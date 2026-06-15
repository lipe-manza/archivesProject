#ifndef IO_H
#define IO_H

#include "data_record.h"
#include <stdio.h>

// Abre um arquivo binário e verifica sua consistência
// Marca como inconsitente se o arquivo for aberto para escrita
// Retorna NULL em caso de falha ou inconsistência
FILE *open_binary_file(char *bin_name, char *mode);

// // Marca o arquivo como inconsistente escrevendo no primeiro byte
// void mark_file_inconsistent(FILE *f_bin);

// Imprime um registro no terminal no formato exigido pelo trabalho
void display_data_record(const DataRecord *record);

// Imprime um registro no formato CSV
void display_data_record_csv(const DataRecord *record);

// Função auxiliar usada para validar arquivo na plataforma
void BinarioNaTela(char *arquivo);

// Leitura segura de strings com aspas
void ScanQuoteString(char *str);

// Lê dados do terminal e monta um novo registro
void read_data_record_from_stdin(DataRecord *new_record);

// Imprime mensagem de cabeçalho no terminal
void print_header_message(char *str);

// Converte string para inteiro de forma segura
// Retorna valor padrão caso a string esteja vazia
int safe_atoi(char *string, int val);

#endif
