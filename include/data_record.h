#ifndef DATA_RECORD_H
#define DATA_RECORD_H

#include <stdbool.h>
#include <stdio.h>

#define RECORD_SIZE 80

// Tipo abstrato que representa um registro de estação
typedef struct data_record_st DataRecord;

// Cria um novo registro com valores iniciais vazios
DataRecord *data_record_create(void);

// Libera a memória do registro
void data_record_destroy(DataRecord **record);

// ==================== Getters e Setters ====================
// Nota: Os setters de strings também atualizam automaticamente os tamanhos dos
// campos

void data_record_set_removido(DataRecord *record, char removido);
char data_record_get_removido(const DataRecord *record);

void data_record_set_proximo(DataRecord *record, int proximo);
int data_record_get_proximo(const DataRecord *record);

void data_record_set_codEstacao(DataRecord *record, int codEstacao);
int data_record_get_codEstacao(const DataRecord *record);

void data_record_set_codLinha(DataRecord *record, int codLinha);
int data_record_get_codLinha(const DataRecord *record);

void data_record_set_codProxEstacao(DataRecord *record, int codProxEstacao);
int data_record_get_codProxEstacao(const DataRecord *record);

void data_record_set_distProxEstacao(DataRecord *record, int distProxEstacao);
int data_record_get_distProxEstacao(const DataRecord *record);

void data_record_set_codLinhaIntegra(DataRecord *record, int codLinhaIntegra);
int data_record_get_codLinhaIntegra(const DataRecord *record);

void data_record_set_codEstIntegra(DataRecord *record, int codEstIntegra);
int data_record_get_codEstIntegra(const DataRecord *record);

void data_record_set_nomeEstacao(DataRecord *record, const char *nome);
const char *data_record_get_nomeEstacao(const DataRecord *record);

void data_record_set_nomeLinha(DataRecord *record, const char *nome);
const char *data_record_get_nomeLinha(const DataRecord *record);

// ==================== Leitura e Escrita em Disco ====================

// Lê um registro do arquivo binário na posição atual
// Trata automaticamente o lixo ('$') no final do registro
bool data_record_read(FILE *bin_file, DataRecord *record);

// Escreve um registro no arquivo binário preenchendo até 80 bytes
bool data_record_write(FILE *bin_file, const DataRecord *record);

// Atualiza um registro em um RRN específico com campos selecionados
bool data_record_update(FILE *bin_file, int RRN, bool fields_to_update[],
                        const DataRecord *updated_data);

#endif
