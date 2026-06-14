#include "../../include/btree.h"
#include <stdlib.h>

// Estados internos da recursão
#define DELETE_OK 0
#define DELETE_UNDERFLOW 1
#define DELETE_NOT_FOUND 2

// ==================== Funções Auxiliares de Remoção ====================

// Empilha uma página removida na lista de reutilização do arquivo
// Marca como removida e atualiza o topo da pilha
static void push_removed_page(FILE *bin_file, BTreeHeader *header, int rrn,
                              BTreePage *page) {
  btree_page_set_removed(page, '1'); // Marca como removido
  btree_page_set_num_of_keys(page, 0);

  // Encadeia na pilha de removidos
  btree_page_set_next_in_stack(page, btree_header_get_top_of_stack(header));

  // Atualiza topo da pilha
  btree_header_set_top_of_stack(header, rrn);

  // Atualiza contagem de nós
  btree_header_set_node_count(header, btree_header_get_node_count(header) - 1);
  btree_page_write(bin_file, page, rrn);
}

// Remove uma chave da página fazendo shift para a esquerda
static void remove_key_from_page(BTreePage *page, int pos) {
  int num_keys = btree_page_get_num_of_keys(page);
  for (int i = pos; i < num_keys - 1; i++) {
    btree_page_set_key(page, i, btree_page_get_key(page, i + 1));
    btree_page_set_child_pointer(page, i + 1,
                                 btree_page_get_child_pointer(page, i + 2));
  }

  // Limpa última posição após shift
  btree_page_set_key(page, num_keys - 1, (BTreeKey){-1, -1});
  btree_page_set_child_pointer(page, num_keys, -1);
  btree_page_set_num_of_keys(page, num_keys - 1);
}

// Encontra o sucessor in-order (menor chave da subárvore direita)
static void find_successor(FILE *bin_file, int child_rrn,
                           BTreeKey *successor_key) {
  BTreePage *page = btree_page_create();
  int current_rrn = child_rrn;

  while (current_rrn != -1) {
    btree_page_read(bin_file, page, current_rrn);

    // Se for folha, o sucessor está na primeira posição
    if (btree_page_get_page_type(page) == PAGE_TYPE_LEAF) {
      *successor_key = btree_page_get_key(page, 0);
      break;
    }

    // Desce sempre pelo filho mais à esquerda
    current_rrn = btree_page_get_child_pointer(page, 0);
  }

  btree_page_destroy(&page);
}

// ==================== Tratamento de Underflow ====================

// Resolve underflow tentando redistribuir ou fazer merge com irmãos
static int handle_underflow(FILE *bin_file, BTreeHeader *header,
                            BTreePage *parent, int child_idx) {

  int child_rrn = btree_page_get_child_pointer(parent, child_idx);

  int left_sibling_rrn =
      (child_idx > 0) ? btree_page_get_child_pointer(parent, child_idx - 1)
                      : -1;

  int right_sibling_rrn =
      (child_idx < btree_page_get_num_of_keys(parent))
          ? btree_page_get_child_pointer(parent, child_idx + 1)
          : -1;

  BTreePage *child = btree_page_create();
  BTreePage *sibling = btree_page_create();

  btree_page_read(bin_file, child, child_rrn);

  int child_keys = btree_page_get_num_of_keys(child);

  // ==================== Caso 1: Redistribuição com irmão da direita
  // ====================
  if (right_sibling_rrn != -1) {
    btree_page_read(bin_file, sibling, right_sibling_rrn);
    int sib_keys = btree_page_get_num_of_keys(sibling);

    // Irmão pode emprestar chave
    if (sib_keys > BTREE_MIN_KEYS) {

      // Desce chave do pai para o filho
      btree_page_set_key(child, child_keys,
                         btree_page_get_key(parent, child_idx));

      // Ajusta ponteiros
      btree_page_set_child_pointer(child, child_keys + 1,
                                   btree_page_get_child_pointer(sibling, 0));

      btree_page_set_num_of_keys(child, child_keys + 1);

      // Sobe menor chave do irmão direito
      btree_page_set_key(parent, child_idx, btree_page_get_key(sibling, 0));

      // Ajusta irmão após remoção
      btree_page_set_child_pointer(sibling, 0,
                                   btree_page_get_child_pointer(sibling, 1));

      remove_key_from_page(sibling, 0);

      btree_page_write(bin_file, child, child_rrn);
      btree_page_write(bin_file, sibling, right_sibling_rrn);

      btree_page_destroy(&child);
      btree_page_destroy(&sibling);

      return DELETE_OK;
    }
  }

  // ==================== Caso 2: Redistribuição com irmão da esquerda
  // ====================
  if (left_sibling_rrn != -1) {
    btree_page_read(bin_file, sibling, left_sibling_rrn);
    int sib_keys = btree_page_get_num_of_keys(sibling);

    if (sib_keys > BTREE_MIN_KEYS) {

      // Abre espaço no filho (shift para direita)
      for (int i = child_keys; i > 0; i--) {
        btree_page_set_key(child, i, btree_page_get_key(child, i - 1));
        btree_page_set_child_pointer(child, i + 1,
                                     btree_page_get_child_pointer(child, i));
      }

      btree_page_set_child_pointer(child, 1,
                                   btree_page_get_child_pointer(child, 0));

      // Desce chave do pai
      btree_page_set_key(child, 0, btree_page_get_key(parent, child_idx - 1));

      // Último ponteiro da esquerda vira filho
      btree_page_set_child_pointer(
          child, 0, btree_page_get_child_pointer(sibling, sib_keys));

      btree_page_set_num_of_keys(child, child_keys + 1);

      // Sobe maior chave do irmão esquerdo
      btree_page_set_key(parent, child_idx - 1,
                         btree_page_get_key(sibling, sib_keys - 1));

      // Limpa irmão
      btree_page_set_key(sibling, sib_keys - 1, (BTreeKey){-1, -1});
      btree_page_set_child_pointer(sibling, sib_keys, -1);
      btree_page_set_num_of_keys(sibling, sib_keys - 1);

      btree_page_write(bin_file, child, child_rrn);
      btree_page_write(bin_file, sibling, left_sibling_rrn);

      btree_page_destroy(&child);
      btree_page_destroy(&sibling);

      return DELETE_OK;
    }
  }

  // ==================== Caso 3: Merge com irmão da esquerda
  // ====================
  if (left_sibling_rrn != -1) {
    btree_page_read(bin_file, sibling, left_sibling_rrn);
    int sib_keys = btree_page_get_num_of_keys(sibling);

    // Desce chave do pai
    btree_page_set_key(sibling, sib_keys,
                       btree_page_get_key(parent, child_idx - 1));

    btree_page_set_child_pointer(sibling, sib_keys + 1,
                                 btree_page_get_child_pointer(child, 0));

    // Copia tudo do filho
    for (int i = 0; i < child_keys; i++) {
      btree_page_set_key(sibling, sib_keys + 1 + i,
                         btree_page_get_key(child, i));
      btree_page_set_child_pointer(sibling, sib_keys + 2 + i,
                                   btree_page_get_child_pointer(child, i + 1));
    }

    btree_page_set_num_of_keys(sibling, sib_keys + 1 + child_keys);

    remove_key_from_page(parent, child_idx - 1);

    push_removed_page(bin_file, header, child_rrn, child);
    btree_page_write(bin_file, sibling, left_sibling_rrn);

    btree_page_destroy(&child);
    btree_page_destroy(&sibling);

    return (btree_page_get_num_of_keys(parent) < BTREE_MIN_KEYS)
               ? DELETE_UNDERFLOW
               : DELETE_OK;
  }

  // ==================== Caso 4: Merge com irmão da direita
  // ====================
  if (right_sibling_rrn != -1) {
    btree_page_read(bin_file, sibling, right_sibling_rrn);
    int sib_keys = btree_page_get_num_of_keys(sibling);

    // Desce chave do pai
    btree_page_set_key(child, child_keys,
                       btree_page_get_key(parent, child_idx));

    btree_page_set_child_pointer(child, child_keys + 1,
                                 btree_page_get_child_pointer(sibling, 0));

    // Copia tudo da direita
    for (int i = 0; i < sib_keys; i++) {
      btree_page_set_key(child, child_keys + 1 + i,
                         btree_page_get_key(sibling, i));

      btree_page_set_child_pointer(
          child, child_keys + 2 + i,
          btree_page_get_child_pointer(sibling, i + 1));
    }

    btree_page_set_num_of_keys(child, child_keys + 1 + sib_keys);

    btree_page_set_child_pointer(parent, child_idx + 1, child_rrn);

    remove_key_from_page(parent, child_idx);

    push_removed_page(bin_file, header, right_sibling_rrn, sibling);
    btree_page_write(bin_file, child, child_rrn);

    btree_page_destroy(&child);
    btree_page_destroy(&sibling);

    return (btree_page_get_num_of_keys(parent) < BTREE_MIN_KEYS)
               ? DELETE_UNDERFLOW
               : DELETE_OK;
  }

  btree_page_destroy(&child);
  btree_page_destroy(&sibling);
  return DELETE_OK;
}

// ==================== Lógica Recursiva Principal ====================

// Função recursiva que desce a árvore procurando a chave e aplicando remoções
static int delete_recursive(FILE *bin_file, BTreeHeader *header,
                            int current_rrn, int search_key) {

  if (current_rrn == -1)
    return DELETE_NOT_FOUND;

  BTreePage *page = btree_page_create();
  btree_page_read(bin_file, page, current_rrn);

  int pos = 0;
  int num_keys = btree_page_get_num_of_keys(page);
  bool found = false;

  // Procura chave na página atual
  while (pos < num_keys) {
    BTreeKey current = btree_page_get_key(page, pos);

    if (current.C == search_key) {
      found = true;
      break;
    } else if (current.C > search_key) {
      break;
    }
    pos++;
  }

  int status;

  if (found) {

    if (btree_page_get_page_type(page) == PAGE_TYPE_LEAF) {
      // Caso 1: remoção direta na folha
      remove_key_from_page(page, pos);
      btree_page_write(bin_file, page, current_rrn);

      int ret = (btree_page_get_num_of_keys(page) < BTREE_MIN_KEYS)
                    ? DELETE_UNDERFLOW
                    : DELETE_OK;

      btree_page_destroy(&page);
      return ret;

    } else {
      // Caso 2: nó interno, troca pelo sucessor
      BTreeKey successor;

      find_successor(bin_file, btree_page_get_child_pointer(page, pos + 1),
                     &successor);

      btree_page_set_key(page, pos, successor);
      btree_page_write(bin_file, page, current_rrn);

      status = delete_recursive(bin_file, header,
                                btree_page_get_child_pointer(page, pos + 1),
                                successor.C);

      pos = pos + 1;
    }

  } else {
    // Desce para o filho correto
    status = delete_recursive(
        bin_file, header, btree_page_get_child_pointer(page, pos), search_key);
  }

  // Trata underflow vindo do nível inferior
  if (status == DELETE_UNDERFLOW) {
    status = handle_underflow(bin_file, header, page, pos);
    btree_page_write(bin_file, page, current_rrn);
  }

  btree_page_destroy(&page);
  return status;
}

// ==================== Função Pública ====================

// Remove uma chave da árvore B
bool btree_delete_key(FILE *bin_file, BTreeHeader *header, int search_key) {
  if (bin_file == NULL || header == NULL)
    return false;

  int root_rrn = btree_header_get_root_node(header);

  if (root_rrn == -1)
    return false;

  int status = delete_recursive(bin_file, header, root_rrn, search_key);

  if (status == DELETE_NOT_FOUND)
    return false;

  // Caso especial: raiz pode encolher
  BTreePage *root_page = btree_page_create();
  btree_page_read(bin_file, root_page, root_rrn);

  if (btree_page_get_num_of_keys(root_page) == 0) {

    int new_root_rrn = btree_page_get_child_pointer(root_page, 0);

    btree_header_set_root_node(header, new_root_rrn);

    if (new_root_rrn != -1) {
      BTreePage *new_root = btree_page_create();
      btree_page_read(bin_file, new_root, new_root_rrn);

      if (btree_page_get_child_pointer(new_root, 0) != -1) {
        btree_page_set_page_type(new_root, PAGE_TYPE_ROOT);
      } else {
        btree_page_set_page_type(new_root, PAGE_TYPE_LEAF);
      }

      btree_page_write(bin_file, new_root, new_root_rrn);
      btree_page_destroy(&new_root);
    }

    push_removed_page(bin_file, header, root_rrn, root_page);
  }

  btree_page_destroy(&root_page);

  // Salva mudanças do cabeçalho
  btree_header_write(bin_file, header);

  return true;
}
