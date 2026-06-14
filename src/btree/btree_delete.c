#include "../../include/btree.h"
#include <stdlib.h>

// Estados internos da recursão
#define DELETE_OK 0
#define DELETE_UNDERFLOW 1
#define DELETE_NOT_FOUND 2

// ==================== Funções Auxiliares de Remoção ====================

/**
 * Empilha uma página que foi esvaziada (destruída) na concatenação,
 * reaproveitando o espaço no disco. (Caso 4)
 */
static void push_removed_page(FILE *bin_file, BTreeHeader *header, int rrn,
                              BTreePage *page) {
  btree_page_set_removed(page, '1'); // Marca como removido
  btree_page_set_num_of_keys(page, 0);

  // O próximo do nó removido aponta para o antigo topo da pilha
  btree_page_set_next_in_stack(page, btree_header_get_top_of_stack(header));

  // O topo do cabeçalho passa a ser este nó recém-removido
  btree_header_set_top_of_stack(header, rrn);

  // Atualiza metadados
  btree_header_set_node_count(header, btree_header_get_node_count(header) - 1);
  btree_page_write(bin_file, page, rrn);
}

/**
 * Remove uma chave (e seu ponteiro da direita) de uma página dando "shift" para
 * a esquerda.
 */
static void remove_key_from_page(BTreePage *page, int pos) {
  int num_keys = btree_page_get_num_of_keys(page);
  for (int i = pos; i < num_keys - 1; i++) {
    btree_page_set_key(page, i, btree_page_get_key(page, i + 1));
    btree_page_set_child_pointer(page, i + 1,
                                 btree_page_get_child_pointer(page, i + 2));
  }
  // Limpa a última posição que ficou duplicada pelo shift
  btree_page_set_key(page, num_keys - 1, (BTreeKey){-1, -1});
  btree_page_set_child_pointer(page, num_keys, -1);
  btree_page_set_num_of_keys(page, num_keys - 1);
}

/**
 * Encontra a chave sucessora imediata (indo uma vez para a direita e tudo para
 * a esquerda). (Caso 2)
 */
static void find_successor(FILE *bin_file, int child_rrn,
                           BTreeKey *successor_key) {
  BTreePage *page = btree_page_create();
  int current_rrn = child_rrn;

  while (current_rrn != -1) {
    btree_page_read(bin_file, page, current_rrn);
    // Se chegou numa folha, o sucessor é o primeiro elemento (índice 0)
    if (btree_page_get_page_type(page) == PAGE_TYPE_LEAF) {
      *successor_key = btree_page_get_key(page, 0);
      break;
    }
    // Desce pelo ponteiro mais à esquerda
    current_rrn = btree_page_get_child_pointer(page, 0);
  }
  btree_page_destroy(&page);
}

// ==================== Tratamento de Underflow ====================

/**
 * Lida com o Underflow (página com 0 chaves) tentanto Redistribuição e depois
 * Concatenação.
 */
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

  // 1. Tenta Redistribuição com a Irmã da Direita
  if (right_sibling_rrn != -1) {
    btree_page_read(bin_file, sibling, right_sibling_rrn);
    int sib_keys = btree_page_get_num_of_keys(sibling);
    if (sib_keys > 1) { // Tem chave sobrando
      int keys_to_take = sib_keys - 1; // Sibling ficará com 1 chave para ser uniforme e priorizar a esquerda
      
      // Desce a chave do pai para o início do filho
      btree_page_set_key(child, 0, btree_page_get_key(parent, child_idx));
      btree_page_set_child_pointer(child, 1, btree_page_get_child_pointer(sibling, 0));

      if (keys_to_take == 2) {
          // Move mais uma chave do sibling para o child
          btree_page_set_key(child, 1, btree_page_get_key(sibling, 0));
          btree_page_set_child_pointer(child, 2, btree_page_get_child_pointer(sibling, 1));
          btree_page_set_num_of_keys(child, 2);
          
          // Sobe a segunda chave da direita (promovida) para o pai
          btree_page_set_key(parent, child_idx, btree_page_get_key(sibling, 1));
          
          // Shift na irmã da direita para remover as duas chaves que saíram
          remove_key_from_page(sibling, 0);
          remove_key_from_page(sibling, 0);
      } else {
          btree_page_set_num_of_keys(child, 1);
          // Sobe a primeira chave da direita (promovida) para o pai
          btree_page_set_key(parent, child_idx, btree_page_get_key(sibling, 0));
          
          // Shift na irmã da direita para remover a chave que subiu
          remove_key_from_page(sibling, 0);
      }

      btree_page_write(bin_file, child, child_rrn);
      btree_page_write(bin_file, sibling, right_sibling_rrn);
      btree_page_destroy(&child);
      btree_page_destroy(&sibling);
      return DELETE_OK;
    }
  }

  // 2. Tenta Redistribuição com a Irmã da Esquerda
  if (left_sibling_rrn != -1) {
    btree_page_read(bin_file, sibling, left_sibling_rrn);
    int sib_keys = btree_page_get_num_of_keys(sibling);
    if (sib_keys > 1) {
      // Desce a chave do pai para o início do filho (que está vazio)
      btree_page_set_key(child, 0, btree_page_get_key(parent, child_idx - 1));
      btree_page_set_child_pointer(
          child, 1, btree_page_get_child_pointer(child, 0)); // Ajusta ponteiro
      btree_page_set_child_pointer(
          child, 0, btree_page_get_child_pointer(sibling, sib_keys));
      btree_page_set_num_of_keys(child, 1);

      // Sobe a última chave da esquerda para o pai
      btree_page_set_key(parent, child_idx - 1,
                         btree_page_get_key(sibling, sib_keys - 1));

      // Remove a chave doente da esquerda
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

  // 3. Concatenação (Merge) - Tenta primeiro com a Esquerda
  if (left_sibling_rrn != -1) {
    btree_page_read(bin_file, sibling, left_sibling_rrn);
    int sib_keys = btree_page_get_num_of_keys(sibling);

    // Desce a chave do pai para a irmã da esquerda
    btree_page_set_key(sibling, sib_keys,
                       btree_page_get_key(parent, child_idx - 1));

    // Copia os ponteiros do filho (que está vazio, então copia o P0) para a
    // esquerda
    btree_page_set_child_pointer(sibling, sib_keys + 1,
                                 btree_page_get_child_pointer(child, 0));
    btree_page_set_num_of_keys(sibling, sib_keys + 1);

    // Remove a chave do pai
    remove_key_from_page(parent, child_idx - 1);

    // Destrói o nó filho (da direita) e salva as alterações
    push_removed_page(bin_file, header, child_rrn, child);
    btree_page_write(bin_file, sibling, left_sibling_rrn);

    btree_page_destroy(&child);
    btree_page_destroy(&sibling);
    // Checa se o pai agora ficou em underflow (Caso 5)
    return (btree_page_get_num_of_keys(parent) < 1) ? DELETE_UNDERFLOW
                                                    : DELETE_OK;
  }

  // 4. Concatenação (Merge) - Por fim, com a Direita
  if (right_sibling_rrn != -1) {
    btree_page_read(bin_file, sibling, right_sibling_rrn);

    // Desce a chave do pai para o filho (que agora é a página da esquerda no
    // merge)
    btree_page_set_key(child, 0, btree_page_get_key(parent, child_idx));
    btree_page_set_num_of_keys(child, 1);

    // Transfere tudo da irmã da direita para o filho
    int sib_keys = btree_page_get_num_of_keys(sibling);
    for (int i = 0; i < sib_keys; i++) {
      btree_page_set_key(child, i + 1, btree_page_get_key(sibling, i));
      btree_page_set_child_pointer(child, i + 1,
                                   btree_page_get_child_pointer(sibling, i));
    }
    btree_page_set_child_pointer(
        child, sib_keys + 1, btree_page_get_child_pointer(sibling, sib_keys));
    btree_page_set_num_of_keys(child, sib_keys + 1);

    // Remove a chave separadora do pai
    remove_key_from_page(parent, child_idx);

    // Destrói a irmã da direita e salva o filho (esquerda do merge)
    push_removed_page(bin_file, header, right_sibling_rrn, sibling);
    btree_page_write(bin_file, child, child_rrn);

    btree_page_destroy(&child);
    btree_page_destroy(&sibling);
    return (btree_page_get_num_of_keys(parent) < 1) ? DELETE_UNDERFLOW
                                                    : DELETE_OK;
  }

  btree_page_destroy(&child);
  btree_page_destroy(&sibling);
  return DELETE_OK;
}

// ==================== Lógica Recursiva Principal ====================

static int delete_recursive(FILE *bin_file, BTreeHeader *header,
                            int current_rrn, int search_key) {
  if (current_rrn == -1)
    return DELETE_NOT_FOUND;

  BTreePage *page = btree_page_create();
  btree_page_read(bin_file, page, current_rrn);

  int pos = 0;
  int num_keys = btree_page_get_num_of_keys(page);
  bool found = false;

  // Procura a chave na página atual
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
      // Caso 1: Chave na folha, apenas arranca
      remove_key_from_page(page, pos);
      btree_page_write(bin_file, page, current_rrn);
      status =
          (btree_page_get_num_of_keys(page) < 1) ? DELETE_UNDERFLOW : DELETE_OK;
    } else {
      // Caso 2: Chave em nó interno, busca o sucessor folha, sobrepõe, e manda
      // deletar o sucessor lá embaixo
      BTreeKey successor;
      find_successor(bin_file, btree_page_get_child_pointer(page, pos + 1),
                     &successor);
      btree_page_set_key(page, pos, successor);      // Sobrepõe
      btree_page_write(bin_file, page, current_rrn); // Atualiza página

      // Continua a deleção recursiva procurando pelo sucessor agora
      status = delete_recursive(bin_file, header,
                                btree_page_get_child_pointer(page, pos + 1),
                                successor.C);
      // Temos que verificar se ocorreu underflow no filho pos+1
      pos = pos + 1; // Para tratar no block final
    }
  } else {
    // Não achou aqui, desce para o filho correspondente
    status = delete_recursive(
        bin_file, header, btree_page_get_child_pointer(page, pos), search_key);
  }

  // Processa Underflow (Casos 3, 4 e 5) que retornou do nível de baixo
  if (status == DELETE_UNDERFLOW) {
    status = handle_underflow(bin_file, header, page, pos);
    btree_page_write(bin_file, page, current_rrn);
  }

  btree_page_destroy(&page);
  return status;
}

// ==================== Função Externa Pública ====================

bool btree_delete_key(FILE *bin_file, BTreeHeader *header, int search_key) {
  if (bin_file == NULL || header == NULL)
    return false;

  int root_rrn = btree_header_get_root_node(header);
  if (root_rrn == -1)
    return false; // Árvore vazia

  int status = delete_recursive(bin_file, header, root_rrn, search_key);

  if (status == DELETE_NOT_FOUND)
    return false;

  // Caso 6: Diminuição da altura da árvore
  // Se a deleção na raiz resultou em underflow (0 chaves)
  BTreePage *root_page = btree_page_create();
  btree_page_read(bin_file, root_page, root_rrn);

  if (btree_page_get_num_of_keys(root_page) == 0) {
    int new_root_rrn = btree_page_get_child_pointer(root_page, 0);

    // Se tiver filho, o filho vira a raiz. Se não tiver, a árvore esvaziou de
    // vez.
    btree_header_set_root_node(header, new_root_rrn);

    if (new_root_rrn != -1) {
      // Atualiza status do novo nó raiz para PAGE_TYPE_ROOT
      BTreePage *new_root = btree_page_create();
      btree_page_read(bin_file, new_root, new_root_rrn);
      if (btree_page_get_page_type(new_root) != PAGE_TYPE_LEAF) {
        btree_page_set_page_type(new_root, PAGE_TYPE_ROOT);
      }
      btree_page_write(bin_file, new_root, new_root_rrn);
      btree_page_destroy(&new_root);
    }

    // Remove a antiga raiz fisicamente e põe na pilha de lixo
    push_removed_page(bin_file, header, root_rrn, root_page);
  }

  btree_page_destroy(&root_page);
  btree_header_write(bin_file,
                     header); // Salva as mudanças cruciais de topo/raiz

  return true;
}
