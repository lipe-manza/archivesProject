#ifndef DATA_RECORD_H
#define DATA_RECORD_H

#include <stdbool.h>
#include <stdio.h>

#define RECORD_SIZE 80

/**
 * @brief Tipo Abstrato de Dados que representa um registro individual de dados
 * (Estação).
 */
typedef struct data_record_st DataRecord;

/**
 * @brief Instancia um novo registro de dados alocando memória e definindo
 * valores nulos.
 * @return Ponteiro para o DataRecord alocado, ou NULL em caso de falha.
 */
DataRecord *data_record_create(void);

/**
 * @brief Libera a memória alocada para o registro de dados.
 * @param record Ponteiro duplo para o registro.
 */
void data_record_destroy(DataRecord **record);

// ==================== Getters & Setters ====================
// Nota: Os setters de strings atualizam automaticamente os campos de tamanho
// (tamNomeEstacao/tamNomeLinha)

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

// ==================== I/O em Disco ====================

/**
 * @brief Lê um registro do arquivo binário a partir da posição atual do
 * ponteiro. Trata automaticamente o consumo do lixo ('$') no final do registro
 * físico.
 * @param bin_file Ponteiro para o arquivo binário.
 * @param record Estrutura que receberá os dados lidos.
 * @return true se a leitura foi bem sucedida, false se chegou ao EOF ou erro.
 */
bool data_record_read(FILE *bin_file, DataRecord *record);

/**
 * @brief Escreve um registro no arquivo binário na posição atual do ponteiro.
 * Preenche o espaço excedente com o caractere de lixo ('$') para atingir 80
 * bytes.
 * @param bin_file Ponteiro para o arquivo binário.
 * @param record Registro a ser gravado.
 * @return true se a escrita ocorreu com sucesso.
 */
bool data_record_write(FILE *bin_file, const DataRecord *record);

/**
 * @brief Atualiza um registro existente em um RRN específico usando campos
 * selecionados.
 * @param bin_file Arquivo binário aberto para leitura/escrita.
 * @param RRN Relative Record Number do registro a ser atualizado.
 * @param fields_to_update Array booleano indicando quais campos devem ser
 * sobrescritos.
 * @param updated_data Registro contendo os novos dados para os campos marcados.
 * @return true se atualizado com sucesso.
 */
bool data_record_update(FILE *bin_file, int RRN, bool fields_to_update[],
                        const DataRecord *updated_data);

#endif
