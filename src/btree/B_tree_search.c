#include <stdbool.h>

#include "../../headers/B_tree.h"

int find_key_in_page(PAGE *page, int key, int *supposedPosition) {

  if (page->removed == '1') {
    return ERROR;
  }

  bool foundKey = false;
  bool foundPos = false;

  for (int i = 0; i < page->numOfKeys && !foundPos; i++) {

    if (page->keys[i].value == key) {
      *supposedPosition = i;
      foundKey = true;
      foundPos = true;
    }

    else if (page->keys[i].value > key) {
      *supposedPosition = i;
      foundPos = true;
    }
  }

  // Se não achou posição dentro do loop significa que é maior que todas
  if (!foundPos) {
    *supposedPosition = page->numOfKeys;
  }

  return foundKey ? IN_PAGE : NOT_IN_PAGE;
}

/* int find_key(FILE *f_arvore_B, PAGE *auxCurrentPage, int RRN, int key, */
/*              int *key_INDEX, int *page_RRN) { */

/*   // Chegou em um no nulo */
/*   if (RRN == -1) */
/*     return ERROR; */

/*   // Le a pagina do RRN atual */
/*   if (!read_B_tree_page_from_bin(f_arvore_B, auxCurrentPage, RRN)) */
/*     return ERROR; */

/*   // Busca pela key */
/*   int index = -1; */

/*   int keyIs = find_key_in_page(auxCurrentPage, key, &index); */

/*   if (keyIs == ERROR) */
/*     return ERROR; */

/*   if (keyIs == IN_PAGE) { */
/*     *key_INDEX = index; */
/*     *page_RRN = RRN; */

/*     return IN_PAGE; */
/*   } */

/*   return find_key(f_arvore_B, auxCurrentPage, */
/*                   auxCurrentPage->childPointer[index], key, key_INDEX, */
/*                   page_RRN); */
/* } */
