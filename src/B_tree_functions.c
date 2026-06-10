#include <stdbool.h>
#include <stdio.h>

#include "../headers/B_tree.h"

bool find_key(FILE *f_arvore_B, PAGE *page, int RRN, int key, int *key_INDEX,
              int *page_RRN) {
  // É folha
  if (RRN == -1)
    return false;
  // Vai para a pagina do RRN atual
  fseek(f_arvore_B, HEADER_SIZE_B_TREE + (RRN * PAGE_SIZE_B_TREE), SEEK_SET);
  // Busca pela key
  int pos = -1;
  int page_has_key = find_key_in_page(f_arvore_B, key, RRN, &pos);

  if (page_has_key) {
    *key_INDEX = pos;
    *page_RRN = RRN;
    return true;
  }

  return find_key(f_arvore_B, page, page->childPointer[pos], key, page_RRN,
                  page_RRN);
}
