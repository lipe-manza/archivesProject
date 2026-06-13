#include <stdbool.h>
#include <stdio.h>

#include "../../include/IO.h"
#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include "../../include/filtro.h"
#include "../../include/sql_functions.h"
#include "../../include/tools.h"

/**
 * @brief Função auxiliar para evitar repetição quando há falha no
 * processamento. Libera toda a memória alocada dinamicamente e fecha arquivos
 * antes do encerramento.
 */
void file_processing_failure_update(FILE **f_bin, DataHeader **header,
                                    DataRecord **filter, DataRecord **updated) {
  if (f_bin != NULL && *f_bin != NULL) {
    fclose(*f_bin);
    *f_bin = NULL;
  }
  if (header != NULL) {
    data_header_destroy(header);
  }
  if (filter != NULL) {
    data_record_destroy(filter);
  }
  if (updated != NULL) {
    data_record_destroy(updated);
  }

  printf("Falha no processamento do arquivo.\n");
}

/**
 * @brief Itera pelos registros do arquivo e atualiza os campos solicitados nos
 * registros que baterem com o filtro.
 */
void update_loop(FILE *f_bin, DataHeader *header, bool *search_for,
                 DataRecord *filter, bool *update_fields,
                 DataRecord *updated_data) {
  if (f_bin == NULL || header == NULL || search_for == NULL || filter == NULL ||
      update_fields == NULL || updated_data == NULL)
    return;

  // Instancia um registro auxiliar para iteração
  DataRecord *record = data_record_create();
  if (record == NULL)
    return;

  int max_records = data_header_get_proxRRN(header);

  // Itera pelos registros do arquivo binário
  for (int rrn = 0; rrn < max_records; rrn++) {
    // Posiciona e lê o registro atual
    fseek(f_bin, HEADER_SIZE + (rrn * RECORD_SIZE), SEEK_SET);

    if (!data_record_read(f_bin, record)) {
      break;
    }

    // Se o registro está removido, ele é pulado
    if (data_record_get_removido(record) == '1')
      continue;

    // Se bater com o filtro, chama a função de atualização física do TAD
    if (match_filter(record, search_for, filter)) {
      data_record_update(f_bin, rrn, update_fields, updated_data);
    }
  }

  data_record_destroy(&record);
}

/**
 * @brief Executa a funcionalidade equivalente a um "UPDATE ... SET ... WHERE"
 * em SQL.
 */
void update_set_where() {
  FILE *f_bin = NULL;
  DataHeader *header = NULL;
  DataRecord *filter = NULL;
  DataRecord *updated = NULL;

  // Lê o nome do arquivo binário
  char bin_name[50];
  if (scanf("%s", bin_name) != 1) {
    file_processing_failure_update(&f_bin, &header, &filter, &updated);
    return;
  }

  // Abre o arquivo binário para leitura e escrita
  f_bin = open_binary_file(bin_name, "rb+");
  if (f_bin == NULL) {
    return;
  }

  // Marca como inconsistente durante as operações
  mark_file_inconsistent(f_bin);

  // Cria e lê a struct do cabeçalho
  header = data_header_create();
  if (header == NULL || !data_header_read(f_bin, header)) {
    file_processing_failure_update(&f_bin, &header, &filter, &updated);
    return;
  }

  // Lê o número de atualizações a serem feitas
  int num_updates;
  if (scanf("%d", &num_updates) != 1) {
    file_processing_failure_update(&f_bin, &header, &filter, &updated);
    return;
  }

  // Itera sobre as sessões de atualização
  for (int i = 0; i < num_updates; i++) {
    // 1. Prepara o filtro (WHERE)
    filter = data_record_create();
    if (filter == NULL) {
      file_processing_failure_update(&f_bin, &header, &filter, &updated);
      return;
    }
    bool search_for[PUBLIC_FIELDS];
    filter_build(filter, search_for);

    // 2. Prepara os novos dados (SET)
    updated = data_record_create();
    if (updated == NULL) {
      file_processing_failure_update(&f_bin, &header, &filter, &updated);
      return;
    }
    bool update_fields[PUBLIC_FIELDS];
    filter_build(updated, update_fields);

    // 3. Aplica a atualização
    update_loop(f_bin, header, search_for, filter, update_fields, updated);

    // Libera a memória para a próxima iteração
    data_record_destroy(&filter);
    data_record_destroy(&updated);
  }

  // Atualiza o número de estações e pares de estações (direto na memória RAM)
  update_statistics(f_bin, header);

  // Grava o cabeçalho consolidado e marca o arquivo como consistente
  data_header_set_status(header, '1');
  data_header_write(f_bin, header);

  // Fecha o arquivo e libera a memória restante
  fclose(f_bin);
  data_header_destroy(&header);

  // Imprime o hash final conforme correção
  BinarioNaTela(bin_name);
}
