#include "../../include/btree.h"
#include <stdlib.h>
#include <string.h>

// Definição real da estrutura da página da Árvore-B.
struct btree_page_st {
  char removido;                   // '1' = removido, '0' = ativo
  int proximo;                     // RRN da próxima página removida
  int tipoNo;                      // -1 = Folha, 0 = Raiz, 1 = Intermediário
  int nroChaves;                   // Quantidade de chaves presentes
  BTreeKey chaves[BTREE_MAX_KEYS]; // Chaves (C) e offsets (Pr)
  int P[BTREE_MAX_CHILDREN];       // Ponteiros para subárvores (RRNs)
};

BTreePage *btree_page_create(void) {
  BTreePage *new_page = (BTreePage *)malloc(sizeof(BTreePage));
  if (new_page == NULL)
    return NULL;

  new_page->removido = '0';
  new_page->proximo = -1;
  new_page->tipoNo = PAGE_TYPE_LEAF;
  new_page->nroChaves = 0;

  for (int i = 0; i < BTREE_MAX_KEYS; i++) {
    new_page->chaves[i].C = -1;
    new_page->chaves[i].Pr = -1;
  }

  for (int i = 0; i < BTREE_MAX_CHILDREN; i++) {
    new_page->P[i] = -1;
  }

  return new_page;
}

void btree_page_destroy(BTreePage **page) {
  if (page != NULL && *page != NULL) {
    free(*page);
    *page = NULL;
  }
}

// ==================== Getters & Setters ====================

void btree_page_set_removed(BTreePage *page, char removed) {
  if (page)
    page->removido = removed;
}

char btree_page_get_removed(const BTreePage *page) {
  return page ? page->removido : '1';
}

void btree_page_set_next_in_stack(BTreePage *page, int next_rrn) {
  if (page)
    page->proximo = next_rrn;
}

int btree_page_get_next_in_stack(const BTreePage *page) {
  return page ? page->proximo : -1;
}

void btree_page_set_page_type(BTreePage *page, int type) {
  if (page)
    page->tipoNo = type;
}

int btree_page_get_page_type(const BTreePage *page) {
  return page ? page->tipoNo : PAGE_TYPE_LEAF;
}

void btree_page_set_num_of_keys(BTreePage *page, int num_keys) {
  if (page)
    page->nroChaves = num_keys;
}

int btree_page_get_num_of_keys(const BTreePage *page) {
  return page ? page->nroChaves : 0;
}

void btree_page_set_key(BTreePage *page, int index, BTreeKey key) {
  if (page && index >= 0 && index < BTREE_MAX_KEYS) {
    page->chaves[index] = key;
  }
}

BTreeKey btree_page_get_key(const BTreePage *page, int index) {
  BTreeKey empty_key = {-1, -1};
  if (page && index >= 0 && index < BTREE_MAX_KEYS) {
    return page->chaves[index];
  }
  return empty_key;
}

void btree_page_set_child_pointer(BTreePage *page, int index, int child_rrn) {
  if (page && index >= 0 && index < BTREE_MAX_CHILDREN) {
    page->P[index] = child_rrn;
  }
}

int btree_page_get_child_pointer(const BTreePage *page, int index) {
  if (page && index >= 0 && index < BTREE_MAX_CHILDREN) {
    return page->P[index];
  }
  return -1;
}

// ==================== I/O em Disco ====================

// Calcula dinamicamente o byte offset de uma página.
long calculate_page_offset(int rrn) {
  return BTREE_HEADER_SIZE + (long)(rrn * BTREE_PAGE_SIZE);
}

bool btree_page_read(FILE *bin_file, BTreePage *page, int rrn) {
  if (bin_file == NULL || page == NULL || rrn < 0)
    return false;

  if (fseek(bin_file, calculate_page_offset(rrn), SEEK_SET) != 0)
    return false;

  if (fread(&page->removido, sizeof(char), 1, bin_file) != 1)
    return false;
  if (fread(&page->proximo, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fread(&page->tipoNo, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fread(&page->nroChaves, sizeof(int), 1, bin_file) != 1)
    return false;

  for (int i = 0; i < BTREE_MAX_KEYS; i++) {
    if (fread(&page->chaves[i].C, sizeof(int), 1, bin_file) != 1)
      return false;
    if (fread(&page->chaves[i].Pr, sizeof(int), 1, bin_file) != 1)
      return false;
  }

  for (int i = 0; i < BTREE_MAX_CHILDREN; i++) {
    if (fread(&page->P[i], sizeof(int), 1, bin_file) != 1)
      return false;
  }

  return true;
}

bool btree_page_write(FILE *bin_file, const BTreePage *page, int rrn) {
  if (bin_file == NULL || page == NULL || rrn < 0)
    return false;

  if (fseek(bin_file, calculate_page_offset(rrn), SEEK_SET) != 0)
    return false;

  if (page->removido == '1') {
    if (fwrite(&page->removido, sizeof(char), 1, bin_file) != 1)
      return false;
    if (fwrite(&page->proximo, sizeof(int), 1, bin_file) != 1)
      return false;
    fflush(bin_file);
    return true;
  }

  if (fwrite(&page->removido, sizeof(char), 1, bin_file) != 1)
    return false;
  if (fwrite(&page->proximo, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fwrite(&page->tipoNo, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fwrite(&page->nroChaves, sizeof(int), 1, bin_file) != 1)
    return false;

  // Garante que lixo de memória não seja escrito no disco para chaves vazias
  for (int i = 0; i < BTREE_MAX_KEYS; i++) {
    int c_val = (i < page->nroChaves) ? page->chaves[i].C : -1;
    int pr_val = (i < page->nroChaves) ? page->chaves[i].Pr : -1;

    if (fwrite(&c_val, sizeof(int), 1, bin_file) != 1)
      return false;
    if (fwrite(&pr_val, sizeof(int), 1, bin_file) != 1)
      return false;
  }

  // Grava ponteiros garantindo que os não-utilizados fiquem como -1
  for (int i = 0; i < BTREE_MAX_CHILDREN; i++) {
    int p_val = (i <= page->nroChaves) ? page->P[i] : -1;
    if (fwrite(&p_val, sizeof(int), 1, bin_file) != 1)
      return false;
  }

  fflush(bin_file);
  return true;
}
