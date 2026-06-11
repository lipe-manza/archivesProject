#include <stdbool.h>
#include <stdio.h>

#include "../../headers/B_tree.h"

int insert_key(FILE *f_arvore_B, int currentRRN, int key, int *promotionKey,
               int *promotionRightChild) {
  // Se chegou no final da tree
  if (currentRRN == -1) {
    *promotionKey = key;
    *promotionRightChild = -1;
    return PROMOTION;
  }

  PAGE *auxCurrentPage;

  // Le a pagina do RRN atual
  if (get_B_tree_page(f_arvore_B, auxCurrentPage, currentRRN))
    return ERROR;

  // Acha a posicao da key(ou suposta) e ve se esta na pagina
  int pos = -1;
  int keyIs = find_key_in_page(f_arvore_B, auxCurrentPage, key, &pos);

  if (keyIs == IN_PAGE) {
    printf("Página já possui a chave");
    return ERROR;
  }

  int promotedRRN = -1;
  int promotedKey = -1;
  int insertStatus = insert_key(f_arvore_B, auxCurrentPage->childPointer[pos],
                                key, &promotedRRN, &promotedKey);

  // Caso não tenha promotion ou houve erro retorna o status
  if (insertStatus == ERROR || insertStatus == NO_PROMOTION) {
    return insertStatus;
  } // Caso tenha espaço na página insere a a promotedKey na página ligada ao no
    // de RRN promotedRRN(que pode ser de um novo nó devido ao split, ou nulo
    // quando nao houver split)
  else if (auxCurrentPage->numOfKeys < MAX_KEYS_PER_PAGE_B_TREE) {
  } else {
  }
}
