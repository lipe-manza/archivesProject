#include "../../include/data_header.h"
#include <stdlib.h>

// --- I/O em Disco ---

bool data_header_read(FILE *bin_file, DataHeader *header) {
  if (bin_file == NULL || header == NULL)
    return false;

  fseek(bin_file, 0, SEEK_SET);
  if (fread(&header->status, sizeof(char), 1, bin_file) != 1)
    return false;
  if (fread(&header->topo, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fread(&header->proxRRN, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fread(&header->nroEstacoes, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fread(&header->nroParesEstacoes, sizeof(int), 1, bin_file) != 1)
    return false;

  return true;
}

bool data_header_write(FILE *bin_file, const DataHeader *header) {
  if (bin_file == NULL || header == NULL)
    return false;

  fseek(bin_file, 0, SEEK_SET);
  if (fwrite(&header->status, sizeof(char), 1, bin_file) != 1)
    return false;
  if (fwrite(&header->topo, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fwrite(&header->proxRRN, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fwrite(&header->nroEstacoes, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fwrite(&header->nroParesEstacoes, sizeof(int), 1, bin_file) != 1)
    return false;

  return true;
}
