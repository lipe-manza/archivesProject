#include "../../include/data_record.h"
#include "../../include/data_header.h"
#include <stdlib.h>
#include <string.h>

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
    char buffer_lixo[81];
    memset(buffer_lixo, '$', lixo_size);
    fwrite(buffer_lixo, sizeof(char), lixo_size, bin_file);
  }

  return true;
}

bool data_record_update(FILE *bin_file, int RRN, bool fields_to_update[],
                        const DataRecord *updated_data) {
  if (bin_file == NULL || updated_data == NULL)
    return false;

  DataRecord current_record;
  memset(&current_record, 0, sizeof(DataRecord));

  // Posiciona o ponteiro e lê o registro atual
  fseek(bin_file, HEADER_SIZE + (RRN * RECORD_SIZE), SEEK_SET);
  if (!data_record_read(bin_file, &current_record)) {
    return false;
  }

  // Aplica as atualizações
  if (fields_to_update[0])
    current_record.codEstacao = updated_data->codEstacao;
  if (fields_to_update[1])
    current_record.codLinha = updated_data->codLinha;
  if (fields_to_update[2])
    current_record.codProxEstacao = updated_data->codProxEstacao;
  if (fields_to_update[3])
    current_record.distProxEstacao = updated_data->distProxEstacao;
  if (fields_to_update[4])
    current_record.codLinhaIntegra = updated_data->codLinhaIntegra;
  if (fields_to_update[5])
    current_record.codEstIntegra = updated_data->codEstIntegra;
  if (fields_to_update[6]) {
    strncpy(current_record.nomeEstacao, updated_data->nomeEstacao, 50);
    current_record.nomeEstacao[50] = '\0';
    current_record.tamNomeEstacao = strlen(current_record.nomeEstacao);
  }
  if (fields_to_update[7]) {
    strncpy(current_record.nomeLinha, updated_data->nomeLinha, 50);
    current_record.nomeLinha[50] = '\0';
    current_record.tamNomeLinha = strlen(current_record.nomeLinha);
  }

  // Volta o ponteiro e sobrescreve
  fseek(bin_file, HEADER_SIZE + (RRN * RECORD_SIZE), SEEK_SET);
  bool status = data_record_write(bin_file, &current_record);

  return status;
}
