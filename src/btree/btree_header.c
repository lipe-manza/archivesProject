#include "../../include/btree.h"
#include <stdlib.h>
#include <string.h>

// ==================== Leitura e Escrita em Disco ====================

bool btree_header_read(FILE *bin_file, BTreeHeader *header) {
  if (bin_file == NULL || header == NULL) {
    return false;
  }

  // Posiciona no início do arquivo para leitura do cabeçalho
  if (fseek(bin_file, 0, SEEK_SET) != 0) {
    return false;
  }

  // Leitura sequencial dos campos do cabeçalho
  if (fread(&header->status, sizeof(char), 1, bin_file) != 1)
    return false;
  if (fread(&header->noRaiz, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fread(&header->topo, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fread(&header->proxRRN, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fread(&header->nroNos, sizeof(int), 1, bin_file) != 1)
    return false;

  return true;
}

bool btree_header_write(FILE *bin_file, const BTreeHeader *header) {
  if (bin_file == NULL || header == NULL) {
    return false;
  }

  // Posiciona no início do arquivo para escrita do cabeçalho
  if (fseek(bin_file, 0, SEEK_SET) != 0) {
    return false;
  }

  // Escrita sequencial dos campos do cabeçalho
  if (fwrite(&header->status, sizeof(char), 1, bin_file) != 1)
    return false;
  if (fwrite(&header->noRaiz, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fwrite(&header->topo, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fwrite(&header->proxRRN, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fwrite(&header->nroNos, sizeof(int), 1, bin_file) != 1)
    return false;

  // Garante persistência imediata no disco
  fflush(bin_file);

  return true;
}
