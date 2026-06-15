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
  page->removido = '1'; // Marca como removido
  page->nroChaves = 0;

  // Encadeia na pilha de removidos
  page->proximo = header->topo;

  // Atualiza topo da pilha
  header->topo = rrn;

  // Atualiza contagem de nós
  header->nroNos = header->nroNos - 1;
  btree_page_write(bin_file, page, rrn);
}

// Remove uma chave da página fazendo shift para a esquerda
static void remove_key_from_page(BTreePage *page, int pos) {
  int num_keys = page->nroChaves;
  for (int i = pos; i < num_keys - 1; i++) {
    page->chaves[i] = page->chaves[i + 1];
    page->P[i + 1] = page->P[i + 2];
  }

  // Limpa última posição após shift
  page->chaves[num_keys - 1] = (BTreeKey){-1, -1};
  page->P[num_keys] = -1;
  page->nroChaves = num_keys - 1;
}

// Encontra o sucessor in-order (menor chave da subárvore direita)
static void find_successor(FILE *bin_file, int child_rrn,
                           BTreeKey *successor_key) {
  BTreePage page;
  int current_rrn = child_rrn;

  while (current_rrn != -1) {
    btree_page_read(bin_file, &page, current_rrn);

    // Se for folha, o sucessor está na primeira posição
    if (page.tipoNo == PAGE_TYPE_LEAF) {
      *successor_key = page.chaves[0];
      break;
    }

    // Desce sempre pelo filho mais à esquerda
    current_rrn = page.P[0];
  }
}

// ==================== Tratamento de Underflow ====================

// Resolve underflow tentando redistribuir ou fazer merge com irmãos
static int handle_underflow(FILE *bin_file, BTreeHeader *header,
                            BTreePage *parent, int child_idx) {

  int child_rrn = parent->P[child_idx];

  int left_sibling_rrn =
      (child_idx > 0) ? parent->P[child_idx - 1] : -1;

  int right_sibling_rrn =
      (child_idx < parent->nroChaves)
          ? parent->P[child_idx + 1] : -1;

  BTreePage child;
  BTreePage sibling;

  btree_page_read(bin_file, &child, child_rrn);

  int child_keys = child.nroChaves;

  // ==================== Caso 1: Redistribuição com irmão da direita
  if (right_sibling_rrn != -1) {
    btree_page_read(bin_file, &sibling, right_sibling_rrn);
    int sib_keys = sibling.nroChaves;

    // Irmão pode emprestar chave
    if (sib_keys > BTREE_MIN_KEYS) {
      // Desce chave do pai para o filho
      child.chaves[child_keys] = parent->chaves[child_idx];

      // Ajusta ponteiros
      child.P[child_keys + 1] = sibling.P[0];

      child.nroChaves = child_keys + 1;

      // Sobe menor chave do irmão direito
      parent->chaves[child_idx] = sibling.chaves[0];

      // Ajusta irmão após remoção
      sibling.P[0] = sibling.P[1];

      remove_key_from_page(&sibling, 0);

      btree_page_write(bin_file, &child, child_rrn);
      btree_page_write(bin_file, &sibling, right_sibling_rrn);

      return DELETE_OK;
    }
  }

  // ==================== Caso 2: Redistribuição com irmão da esquerda
  if (left_sibling_rrn != -1) {
    btree_page_read(bin_file, &sibling, left_sibling_rrn);
    int sib_keys = sibling.nroChaves;

    if (sib_keys > BTREE_MIN_KEYS) {
      // Abre espaço no filho (shift para direita)
      for (int i = child_keys; i > 0; i--) {
        child.chaves[i] = child.chaves[i - 1];
        child.P[i + 1] = child.P[i];
      }

      child.P[1] = child.P[0];

      // Desce chave do pai
      child.chaves[0] = parent->chaves[child_idx - 1];

      // Último ponteiro da esquerda vira filho
      child.P[0] = sibling.P[sib_keys];

      child.nroChaves = child_keys + 1;

      // Sobe maior chave do irmão esquerdo
      parent->chaves[child_idx - 1] = sibling.chaves[sib_keys - 1];

      // Limpa irmão
      sibling.chaves[sib_keys - 1] = (BTreeKey){-1, -1};
      sibling.P[sib_keys] = -1;
      sibling.nroChaves = sib_keys - 1;

      btree_page_write(bin_file, &child, child_rrn);
      btree_page_write(bin_file, &sibling, left_sibling_rrn);

      return DELETE_OK;
    }
  }

  // ==================== Caso 3: Merge com irmão da esquerda
  if (left_sibling_rrn != -1) {
    btree_page_read(bin_file, &sibling, left_sibling_rrn);
    int sib_keys = sibling.nroChaves;

    // Desce chave do pai
    sibling.chaves[sib_keys] = parent->chaves[child_idx - 1];

    sibling.P[sib_keys + 1] = child.P[0];

    // Copia tudo do filho
    for (int i = 0; i < child_keys; i++) {
      sibling.chaves[sib_keys + 1 + i] = child.chaves[i];
      sibling.P[sib_keys + 2 + i] = child.P[i + 1];
    }

    sibling.nroChaves = sib_keys + 1 + child_keys;

    remove_key_from_page(parent, child_idx - 1);

    push_removed_page(bin_file, header, child_rrn, &child);
    btree_page_write(bin_file, &sibling, left_sibling_rrn);

    return (parent->nroChaves < BTREE_MIN_KEYS)
               ? DELETE_UNDERFLOW
               : DELETE_OK;
  }

  // ==================== Caso 4: Merge com irmão da direita
  if (right_sibling_rrn != -1) {
    btree_page_read(bin_file, &sibling, right_sibling_rrn);
    int sib_keys = sibling.nroChaves;

    // Desce chave do pai
    child.chaves[child_keys] = parent->chaves[child_idx];

    child.P[child_keys + 1] = sibling.P[0];

    // Copia tudo da direita
    for (int i = 0; i < sib_keys; i++) {
      child.chaves[child_keys + 1 + i] = sibling.chaves[i];

      child.P[child_keys + 2 + i] = sibling.P[i + 1];
    }

    child.nroChaves = child_keys + 1 + sib_keys;

    parent->P[child_idx + 1] = child_rrn;

    remove_key_from_page(parent, child_idx);

    push_removed_page(bin_file, header, right_sibling_rrn, &sibling);
    btree_page_write(bin_file, &child, child_rrn);

    return (parent->nroChaves < BTREE_MIN_KEYS)
               ? DELETE_UNDERFLOW
               : DELETE_OK;
  }

  return DELETE_OK;
}

// ==================== Lógica Recursiva Principal ====================

// Função recursiva que desce a árvore procurando a chave e aplicando remoções
static int delete_recursive(FILE *bin_file, BTreeHeader *header,
                            int current_rrn, int search_key) {

  if (current_rrn == -1)
    return DELETE_NOT_FOUND;

  BTreePage page;
  btree_page_read(bin_file, &page, current_rrn);

  int pos = 0;
  int num_keys = page.nroChaves;
  bool found = false;

  // Procura chave na página atual
  while (pos < num_keys) {
    BTreeKey current = page.chaves[pos];

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

    if (page.tipoNo == PAGE_TYPE_LEAF) {
      // Caso 1: remoção direta na folha
      remove_key_from_page(&page, pos);
      btree_page_write(bin_file, &page, current_rrn);

      int ret = (page.nroChaves < BTREE_MIN_KEYS)
                    ? DELETE_UNDERFLOW
                    : DELETE_OK;

      return ret;

    } else {
      // Caso 2: nó interno, troca pelo sucessor
      BTreeKey successor;

      find_successor(bin_file, page.P[pos + 1],
                     &successor);

      page.chaves[pos] = successor;
      btree_page_write(bin_file, &page, current_rrn);

      status = delete_recursive(bin_file, header,
                                page.P[pos + 1],
                                successor.C);

      pos = pos + 1;
    }

  } else {
    // Desce para o filho correto
    status = delete_recursive(
        bin_file, header, page.P[pos], search_key);
  }

  // Trata underflow vindo do nível inferior
  if (status == DELETE_UNDERFLOW) {
    status = handle_underflow(bin_file, header, &page, pos);
    btree_page_write(bin_file, &page, current_rrn);
  }

  return status;
}

// ==================== Função Pública ====================

// Remove uma chave da árvore B
bool btree_delete_key(FILE *bin_file, BTreeHeader *header, int search_key) {
  if (bin_file == NULL || header == NULL)
    return false;

  int root_rrn = header->noRaiz;

  if (root_rrn == -1)
    return false;

  int status = delete_recursive(bin_file, header, root_rrn, search_key);

  if (status == DELETE_NOT_FOUND)
    return false;

  // Caso especial: raiz pode encolher
  BTreePage root_page;
  btree_page_read(bin_file, &root_page, root_rrn);

  if (root_page.nroChaves == 0) {

    int new_root_rrn = root_page.P[0];

    header->noRaiz = new_root_rrn;

    if (new_root_rrn != -1) {
      BTreePage new_root;
      btree_page_read(bin_file, &new_root, new_root_rrn);

      if (new_root.P[0] != -1) {
        new_root.tipoNo = PAGE_TYPE_ROOT;
      } else {
        new_root.tipoNo = PAGE_TYPE_LEAF;
      }

      btree_page_write(bin_file, &new_root, new_root_rrn);
    }

    push_removed_page(bin_file, header, root_rrn, &root_page);
  }

  // Salva mudanças do cabeçalho
  btree_header_write(bin_file, header);

  return true;
}
