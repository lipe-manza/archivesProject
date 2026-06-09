#include <stdio.h>

#include "../headers/arvoreB.h"

int search_key(FILE *p_bin, NO_AB *no, int key) {
  // Le se o no ta removido, impossivel estar na busca
  fread(&no->removido, sizeof(int), 1, p_bin);
  // Le o proximo no da pilha
  fread(&no->proximo, sizeof(int), 1, p_bin);
  // Le o tipo do no
  fread(&no->tipoNo, sizeof(int), 1, p_bin);
  // Le o numero de chaves
  fread(&no->nroChaves, sizeof(int), 1, p_bin);
  int index = -1;
  for (int i = 0; i < no->nroChaves; i++) {
    fread(no->chaves[i], sizeof(int), 1, p_bin);
    if (key_atual == key) {
      *pos_key = i;
      break;
    } else if (key_atual > key) {
    }
    if ()
  }
}
bool search_ab(FILE *p_bin, int RRN, int key, int *found_RRN, int *found_POS) {

  if (RRN == -1)
    return false;
}
