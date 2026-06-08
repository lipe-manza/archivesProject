#include <stdio.h>

#include "../headers/arvoreB.h"

void search_key(FILE *p_bin, int *pos_key, int *tipo_no, int *RRN_child_pos,
                int key) {

  // Pula o removido e o proxRRN ja que nunca vai ter um removido na busca
  fseek(p_bin, 5, SEEK_CUR);
  // Le o tipo do no
  int tipo_no = -1;
  fread(&tipo_no, sizeof(int), p_bin);
  // Le o numero de chaves
  int nroChaves = 0;
  fread(&nroChaves, sizeof(int), p_bin);
  int key_atual = 0;
  for (int i = 0; i < nroChaves; i++) {
    fread(&key_atual, sizeof(int), p_bin);
    if (key_atual == key) {
      *pos_key = i + 1;
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
