#ifndef DATA_HEADER_H
#define DATA_HEADER_H

#include <stdbool.h>
#include <stdio.h>

#define HEADER_SIZE 17

// Tipo abstrato que representa o cabeçalho do arquivo de dados
typedef struct data_header_st DataHeader;

// Cria um novo cabeçalho com valores padrão (inconsistente e vazio)
DataHeader *data_header_create(void);

// Cria um cabeçalho já preenchido com valores específicos
DataHeader *data_header_build(char status, int topo, int proxRRN,
                              int nroEstacoes, int nroParesEstacoes);

// Libera a memória do cabeçalho
void data_header_destroy(DataHeader **header);

// ==================== Getters e Setters ====================

void data_header_set_status(DataHeader *header, char status);
char data_header_get_status(const DataHeader *header);

void data_header_set_topo(DataHeader *header, int topo);
int data_header_get_topo(const DataHeader *header);

void data_header_set_proxRRN(DataHeader *header, int proxRRN);
int data_header_get_proxRRN(const DataHeader *header);

void data_header_set_nroEstacoes(DataHeader *header, int nroEstacoes);
int data_header_get_nroEstacoes(const DataHeader *header);

void data_header_set_nroParesEstacoes(DataHeader *header, int nroParesEstacoes);
int data_header_get_nroParesEstacoes(const DataHeader *header);

// ==================== Leitura e Escrita em Disco ====================

// Lê o cabeçalho diretamente do início do arquivo binário
bool data_header_read(FILE *bin_file, DataHeader *header);

// Escreve o cabeçalho no início do arquivo binário
bool data_header_write(FILE *bin_file, const DataHeader *header);

#endif
