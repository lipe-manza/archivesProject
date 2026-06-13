#ifndef DATA_HEADER_H
#define DATA_HEADER_H

#include <stdbool.h>
#include <stdio.h>

#define HEADER_SIZE 17

/**
 * @brief Tipo Abstrato de Dados que representa o registro de cabeçalho do
 * arquivo de dados.
 */
typedef struct data_header_st DataHeader;

/**
 * @brief Instancia um novo registro de cabeçalho com valores padrão
 * (inconsistente e vazio).
 * @return Ponteiro para o DataHeader alocado, ou NULL em caso de falha.
 */
DataHeader *data_header_create(void);

/**
 * @brief Instancia um novo registro de cabeçalho com valores específicos.
 */
DataHeader *data_header_build(char status, int topo, int proxRRN,
                              int nroEstacoes, int nroParesEstacoes);

/**
 * @brief Libera a memória alocada para o registro de cabeçalho.
 * @param header Ponteiro duplo para o cabeçalho.
 */
void data_header_destroy(DataHeader **header);

// ==================== Getters & Setters ====================

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

// ==================== I/O em Disco ====================

/**
 * @brief Lê o registro de cabeçalho diretamente do início do arquivo binário.
 * @param bin_file Ponteiro para o arquivo binário aberto para leitura.
 * @param header Estrutura onde os dados serão armazenados.
 * @return true se a leitura foi bem-sucedida, false caso contrário.
 */
bool data_header_read(FILE *bin_file, DataHeader *header);

/**
 * @brief Escreve o registro de cabeçalho no início do arquivo binário.
 * @param bin_file Ponteiro para o arquivo binário aberto para escrita.
 * @param header Estrutura com os dados a serem escritos.
 * @return true se a escrita foi bem-sucedida, false caso contrário.
 */
bool data_header_write(FILE *bin_file, const DataHeader *header);

#endif
