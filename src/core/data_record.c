#include "../../include/data_record.h"
#include "../../include/data_header.h"
#include <stdlib.h>
#include <string.h>

struct data_record_st {
  char removido;
  int proximo;
  int codEstacao;
  int codLinha;
  int codProxEstacao;
  int distProxEstacao;
  int codLinhaIntegra;
  int codEstIntegra;
  int tamNomeEstacao;
  char nomeEstacao[51];
  int tamNomeLinha;
  char nomeLinha[51];
};

DataRecord *data_record_create(void) {
  DataRecord *new_record = (DataRecord *)malloc(sizeof(DataRecord));
  if (new_record != NULL) {
    new_record->removido = '0';
    new_record->proximo = -1;
    new_record->codEstacao = -1;
    new_record->codLinha = -1;
    new_record->codProxEstacao = -1;
    new_record->distProxEstacao = -1;
    new_record->codLinhaIntegra = -1;
    new_record->codEstIntegra = -1;
    new_record->tamNomeEstacao = 0;
    memset(new_record->nomeEstacao, 0, 51);
    new_record->tamNomeLinha = 0;
    memset(new_record->nomeLinha, 0, 51);
  }
  return new_record;
}

void data_record_destroy(DataRecord **record) {
  if (record != NULL && *record != NULL) {
    free(*record);
    *record = NULL;
  }
}

// --- Getters e Setters ---

void data_record_set_removido(DataRecord *record, char removido) {
  if (record)
    record->removido = removido;
}
char data_record_get_removido(const DataRecord *record) {
  return record ? record->removido : '1';
}

void data_record_set_proximo(DataRecord *record, int proximo) {
  if (record)
    record->proximo = proximo;
}
int data_record_get_proximo(const DataRecord *record) {
  return record ? record->proximo : -1;
}

void data_record_set_codEstacao(DataRecord *record, int codEstacao) {
  if (record)
    record->codEstacao = codEstacao;
}
int data_record_get_codEstacao(const DataRecord *record) {
  return record ? record->codEstacao : -1;
}

void data_record_set_codLinha(DataRecord *record, int codLinha) {
  if (record)
    record->codLinha = codLinha;
}
int data_record_get_codLinha(const DataRecord *record) {
  return record ? record->codLinha : -1;
}

void data_record_set_codProxEstacao(DataRecord *record, int codProxEstacao) {
  if (record)
    record->codProxEstacao = codProxEstacao;
}
int data_record_get_codProxEstacao(const DataRecord *record) {
  return record ? record->codProxEstacao : -1;
}

void data_record_set_distProxEstacao(DataRecord *record, int distProxEstacao) {
  if (record)
    record->distProxEstacao = distProxEstacao;
}
int data_record_get_distProxEstacao(const DataRecord *record) {
  return record ? record->distProxEstacao : -1;
}

void data_record_set_codLinhaIntegra(DataRecord *record, int codLinhaIntegra) {
  if (record)
    record->codLinhaIntegra = codLinhaIntegra;
}
int data_record_get_codLinhaIntegra(const DataRecord *record) {
  return record ? record->codLinhaIntegra : -1;
}

void data_record_set_codEstIntegra(DataRecord *record, int codEstIntegra) {
  if (record)
    record->codEstIntegra = codEstIntegra;
}
int data_record_get_codEstIntegra(const DataRecord *record) {
  return record ? record->codEstIntegra : -1;
}

void data_record_set_nomeEstacao(DataRecord *record, const char *nome) {
  if (record != NULL && nome != NULL) {
    strncpy(record->nomeEstacao, nome, 50);
    record->nomeEstacao[50] = '\0';
    record->tamNomeEstacao = strlen(record->nomeEstacao);
  }
}
const char *data_record_get_nomeEstacao(const DataRecord *record) {
  return record ? record->nomeEstacao : NULL;
}

void data_record_set_nomeLinha(DataRecord *record, const char *nome) {
  if (record != NULL && nome != NULL) {
    strncpy(record->nomeLinha, nome, 50);
    record->nomeLinha[50] = '\0';
    record->tamNomeLinha = strlen(record->nomeLinha);
  }
}
const char *data_record_get_nomeLinha(const DataRecord *record) {
  return record ? record->nomeLinha : NULL;
}

// --- I/O em Disco ---

bool data_record_read(FILE *bin_file, DataRecord *record) {
  if (bin_file == NULL || record == NULL)
    return false;

  long pos_inicial = ftell(bin_file);

  if (fread(&record->removido, sizeof(char), 1, bin_file) != 1)
    return false;

  if (record->removido == '1') {
    fseek(bin_file, RECORD_SIZE - 1, SEEK_CUR);
    return true;
  }

  if (fread(&record->proximo, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fread(&record->codEstacao, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fread(&record->codLinha, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fread(&record->codProxEstacao, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fread(&record->distProxEstacao, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fread(&record->codLinhaIntegra, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fread(&record->codEstIntegra, sizeof(int), 1, bin_file) != 1)
    return false;

  if (fread(&record->tamNomeEstacao, sizeof(int), 1, bin_file) != 1)
    return false;
  if (record->tamNomeEstacao > 0) {
    if (fread(record->nomeEstacao, sizeof(char), record->tamNomeEstacao,
              bin_file) != (size_t)record->tamNomeEstacao)
      return false;
    record->nomeEstacao[record->tamNomeEstacao] = '\0';
  } else {
    record->nomeEstacao[0] = '\0';
  }

  if (fread(&record->tamNomeLinha, sizeof(int), 1, bin_file) != 1)
    return false;
  if (record->tamNomeLinha > 0) {
    if (fread(record->nomeLinha, sizeof(char), record->tamNomeLinha,
              bin_file) != (size_t)record->tamNomeLinha)
      return false;
    record->nomeLinha[record->tamNomeLinha] = '\0';
  } else {
    record->nomeLinha[0] = '\0';
  }

  long bytes_lidos = ftell(bin_file) - pos_inicial;
  long bytes_restantes = RECORD_SIZE - bytes_lidos;

  // Consome o lixo ('$')
  if (bytes_restantes > 0) {
    fseek(bin_file, bytes_restantes, SEEK_CUR);
  }

  return true;
}

bool data_record_write(FILE *bin_file, const DataRecord *record) {
  if (bin_file == NULL || record == NULL)
    return false;

  fwrite(&record->removido, sizeof(char), 1, bin_file);
  fwrite(&record->proximo, sizeof(int), 1, bin_file);
  fwrite(&record->codEstacao, sizeof(int), 1, bin_file);
  fwrite(&record->codLinha, sizeof(int), 1, bin_file);
  fwrite(&record->codProxEstacao, sizeof(int), 1, bin_file);
  fwrite(&record->distProxEstacao, sizeof(int), 1, bin_file);
  fwrite(&record->codLinhaIntegra, sizeof(int), 1, bin_file);
  fwrite(&record->codEstIntegra, sizeof(int), 1, bin_file);

  fwrite(&record->tamNomeEstacao, sizeof(int), 1, bin_file);
  if (record->tamNomeEstacao > 0) {
    fwrite(record->nomeEstacao, sizeof(char), record->tamNomeEstacao, bin_file);
  }

  fwrite(&record->tamNomeLinha, sizeof(int), 1, bin_file);
  if (record->tamNomeLinha > 0) {
    fwrite(record->nomeLinha, sizeof(char), record->tamNomeLinha, bin_file);
  }

  // Preenchimento com lixo
  int bytes_usados = 37 + record->tamNomeEstacao + record->tamNomeLinha;
  int lixo_size = RECORD_SIZE - bytes_usados;

  if (lixo_size > 0) {
    char buffer_lixo[41];
    memset(buffer_lixo, '$', lixo_size);
    fwrite(buffer_lixo, sizeof(char), lixo_size, bin_file);
  }

  return true;
}

bool data_record_update(FILE *bin_file, int RRN, bool fields_to_update[],
                        const DataRecord *updated_data) {
  if (bin_file == NULL || updated_data == NULL)
    return false;

  DataRecord *current_record = data_record_create();

  // Posiciona o ponteiro e lê o registro atual
  fseek(bin_file, HEADER_SIZE + (RRN * RECORD_SIZE), SEEK_SET);
  if (!data_record_read(bin_file, current_record)) {
    data_record_destroy(&current_record);
    return false;
  }

  // Aplica as atualizações usando os setters
  if (fields_to_update[0])
    data_record_set_codEstacao(current_record, updated_data->codEstacao);
  if (fields_to_update[1])
    data_record_set_codLinha(current_record, updated_data->codLinha);
  if (fields_to_update[2])
    data_record_set_codProxEstacao(current_record,
                                   updated_data->codProxEstacao);
  if (fields_to_update[3])
    data_record_set_distProxEstacao(current_record,
                                    updated_data->distProxEstacao);
  if (fields_to_update[4])
    data_record_set_codLinhaIntegra(current_record,
                                    updated_data->codLinhaIntegra);
  if (fields_to_update[5])
    data_record_set_codEstIntegra(current_record, updated_data->codEstIntegra);
  if (fields_to_update[6])
    data_record_set_nomeEstacao(current_record, updated_data->nomeEstacao);
  if (fields_to_update[7])
    data_record_set_nomeLinha(current_record, updated_data->nomeLinha);

  // Volta o ponteiro e sobrescreve
  fseek(bin_file, HEADER_SIZE + (RRN * RECORD_SIZE), SEEK_SET);
  bool status = data_record_write(bin_file, current_record);

  data_record_destroy(&current_record);
  return status;
}
