#ifndef DATA_HEADER_H
#define DATA_HEADER_H

#include <stdbool.h>
#include <stdio.h>

#define HEADER_SIZE 17

typedef struct {
  char status;
  int topo;
  int proxRRN;
  int nroEstacoes;
  int nroParesEstacoes;
} DataHeader;

// ==================== Leitura e Escrita em Disco ====================

// Lê o cabeçalho diretamente do início do arquivo binário
bool data_header_read(FILE *bin_file, DataHeader *header);

// Escreve o cabeçalho no início do arquivo binário
bool data_header_write(FILE *bin_file, const DataHeader *header);

#endif
