#include <stdio.h>

#include "../headers/arvoreB.h"

bool read_no_from_bin(FILE *p_bin, NO_AB *no) {

  if (fread(&no->removido, sizeof(no->removido), 1, p_bin) != 1)
    return false;

  if (fread(&no->proximo, sizeof(no->proximo), 1, p_bin) != 1)
    return false;

  if (fread(&no->tipoNo, sizeof(no->tipoNo), 1, p_bin) != 1)
    return false;

  if (fread(&no->nroChaves, sizeof(no->nroChaves), 1, p_bin) != 1)
    return false;

  if (fread(&no->c1, sizeof(no->c1), 1, p_bin) != 1)
    return false;
  if (fread(&no->pr1, sizeof(no->pr1), 1, p_bin) != 1)
    return false;

  if (fread(&no->c2, sizeof(no->c2), 1, p_bin) != 1)
    return false;
  if (fread(&no->pr2, sizeof(no->pr2), 1, p_bin) != 1)
    return false;

  if (fread(&no->c3, sizeof(no->c3), 1, p_bin) != 1)
    return false;
  if (fread(&no->pr3, sizeof(no->pr3), 1, p_bin) != 1)
    return false;

  if (fread(&no->p1, sizeof(no->p1), 1, p_bin) != 1)
    return false;
  if (fread(&no->p2, sizeof(no->p2), 1, p_bin) != 1)
    return false;
  if (fread(&no->p3, sizeof(no->p3), 1, p_bin) != 1)
    return false;
  if (fread(&no->p4, sizeof(no->p4), 1, p_bin) != 1)
    return false;

  return true;
}

void write_no_in_bin(FILE *f_bin, NO_AB *no) {

  fwrite(&no->removido, sizeof(no->removido), 1, f_bin);
  fwrite(&no->proximo, sizeof(no->proximo), 1, f_bin);
  fwrite(&no->tipoNo, sizeof(no->tipoNo), 1, f_bin);
  fwrite(&no->nroChaves, sizeof(no->nroChaves), 1, f_bin);

  fwrite(&no->c1, sizeof(no->c1), 1, f_bin);
  fwrite(&no->pr1, sizeof(no->pr1), 1, f_bin);

  fwrite(&no->c2, sizeof(no->c2), 1, f_bin);
  fwrite(&no->pr2, sizeof(no->pr2), 1, f_bin);

  fwrite(&no->c3, sizeof(no->c3), 1, f_bin);
  fwrite(&no->pr3, sizeof(no->pr3), 1, f_bin);

  fwrite(&no->p1, sizeof(no->p1), 1, f_bin);
  fwrite(&no->p2, sizeof(no->p2), 1, f_bin);
  fwrite(&no->p3, sizeof(no->p3), 1, f_bin);
  fwrite(&no->p4, sizeof(no->p4), 1, f_bin);
}
