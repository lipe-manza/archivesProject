#include "../../include/btree.h"
#include <stdlib.h>
#include <string.h>

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
