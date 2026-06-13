#ifndef IO_H
#define IO_H

#include "data_record.h"
#include <stdio.h>

/**
 * @brief Abre um arquivo binário e verifica a sua consistência.
 * @param bin_name Nome do arquivo.
 * @param mode Modo de acesso ao arquivo (ex: "rb+", "wb").
 * @return Ponteiro para o arquivo aberto, ou NULL em caso de
 * falha/inconsistência.
 */
FILE *open_binary_file(char *bin_name, char *mode);

/**
 * @brief Vai até o primeiro byte do arquivo, escreve '0' para marcá-lo como
 * inconsistente e força a gravação no disco.
 * @param f_bin Ponteiro para o arquivo binário.
 */
void mark_file_inconsistent(FILE *f_bin);

/**
 * @brief Imprime os dados de um registro no terminal conforme a formatação
 * exigida.
 * @param record Registro de dados a ser impresso.
 */
void display_data_record(const DataRecord *record);

/**
 * @brief Imprime os dados de um registro em formato CSV.
 * @param record Registro de dados a ser impresso.
 */
void display_data_record_csv(const DataRecord *record);

void BinarioNaTela(char *arquivo);

void ScanQuoteString(char *str);

/**
 * @brief Lê campos digitados no terminal e preenche um novo registro de dados.
 * @param new_record Registro vazio que receberá os dados lidos.
 */
void read_data_record_from_stdin(DataRecord *new_record);

/**
 * @brief Imprime a mensagem de cabeçalho.
 * @param str String do cabeçalho.
 */
void print_header_message(char *str);

/**
 * @brief Conversão segura de ASCII para Inteiro. Retorna um valor padrão se a
 * string for vazia.
 * @param string String a ser convertida.
 * @param val Valor padrão caso a string seja vazia.
 */
int safe_atoi(char *string, int val);

#endif
