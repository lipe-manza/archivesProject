#include "../../include/data_header.h"
#include <stdlib.h>

struct data_header_st {
  char status;
  int topo;
  int proxRRN;
  int nroEstacoes;
  int nroParesEstacoes;
};

// --- Construtores ---

DataHeader *data_header_create(void) {
  DataHeader *new_header = (DataHeader *)malloc(sizeof(DataHeader));
  if (new_header != NULL) {
    new_header->status = '0';
    new_header->topo = -1;
    new_header->proxRRN = 0;
    new_header->nroEstacoes = 0;
    new_header->nroParesEstacoes = 0;
  }
  return new_header;
}

DataHeader *data_header_build(char status, int topo, int proxRRN,
                              int nroEstacoes, int nroParesEstacoes) {
  DataHeader *new_header = (DataHeader *)malloc(sizeof(DataHeader));
  if (new_header != NULL) {
    new_header->status = status;
    new_header->topo = topo;
    new_header->proxRRN = proxRRN;
    new_header->nroEstacoes = nroEstacoes;
    new_header->nroParesEstacoes = nroParesEstacoes;
  }
  return new_header;
}

// --- Destrutor ---

void data_header_destroy(DataHeader **header) {
  if (header != NULL && *header != NULL) {
    free(*header);
    *header = NULL;
  }
}

// --- Getters e Setters ---

void data_header_set_status(DataHeader *header, char status) {
  if (header)
    header->status = status;
}
char data_header_get_status(const DataHeader *header) {
  return header ? header->status : '0';
}

void data_header_set_topo(DataHeader *header, int topo) {
  if (header)
    header->topo = topo;
}
int data_header_get_topo(const DataHeader *header) {
  return header ? header->topo : -1;
}

void data_header_set_proxRRN(DataHeader *header, int proxRRN) {
  if (header)
    header->proxRRN = proxRRN;
}
int data_header_get_proxRRN(const DataHeader *header) {
  return header ? header->proxRRN : -1;
}

void data_header_set_nroEstacoes(DataHeader *header, int nroEstacoes) {
  if (header)
    header->nroEstacoes = nroEstacoes;
}
int data_header_get_nroEstacoes(const DataHeader *header) {
  return header ? header->nroEstacoes : -1;
}

void data_header_set_nroParesEstacoes(DataHeader *header,
                                      int nroParesEstacoes) {
  if (header)
    header->nroParesEstacoes = nroParesEstacoes;
}
int data_header_get_nroParesEstacoes(const DataHeader *header) {
  return header ? header->nroParesEstacoes : -1;
}

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
