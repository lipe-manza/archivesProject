#include <stdbool.h>
#include <stdio.h>

#include "../../include/IO.h"
#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include "../../include/filtro.h"
#include "../../include/sql_functions.h"
#include "../../include/tools.h"

// Função auxiliar para evitar repetição quando há falha no
// processamento. Fecha arquivos abertos antes de exibir a mensagem de erro.
void file_processing_failure_update(FILE **f_bin) {
  if (f_bin != NULL && *f_bin != NULL) {
    fclose(*f_bin);
    *f_bin = NULL;
  }

  printf("Falha no processamento do arquivo.\n");
}

// Itera pelos registros do arquivo e atualiza os campos solicitados nos
// registros que baterem com o filtro.
void update_loop(FILE *f_bin, DataHeader *header, bool *search_for,
                 DataRecord *filter, bool *update_fields,
                 DataRecord *updated_data) {
  if (f_bin == NULL || header == NULL || search_for == NULL || filter == NULL ||
      update_fields == NULL || updated_data == NULL)
    return;

  // Instancia um registro auxiliar para iteração
  DataRecord record;

  int max_records = header->proxRRN;

  // Itera pelos registros do arquivo binário
  for (int rrn = 0; rrn < max_records; rrn++) {
    // Posiciona e lê o registro atual
    fseek(f_bin, HEADER_SIZE + (rrn * RECORD_SIZE), SEEK_SET);

    if (!data_record_read(f_bin, &record)) {
      break;
    }

    // Se o registro está removido, ele é pulado
    if (record.removido == '1')
      continue;

    // Se bater com o filtro, chama a função de atualização física da struct
    if (match_filter(&record, search_for, filter)) {
      data_record_update(f_bin, rrn, update_fields, updated_data);
    }

    // Se tiver o mesmo 'codEstacao' do filtro, encerra a busca
    if (match_codEstacao(&record, search_for, filter))
      break;
  }
}

// Atualiza os registros não removidos que batem com o filtro
void update_set_where() {
  FILE *f_bin = NULL;
  DataHeader header = {0};

  // Lê o nome do arquivo binário
  char bin_name[50];
  if (scanf("%s", bin_name) != 1) {
    file_processing_failure_update(&f_bin);
    return;
  }

  // Abre o arquivo binário para leitura e escrita
  f_bin = open_binary_file(bin_name, "rb+");
  if (f_bin == NULL) {
    file_processing_failure_update(&f_bin);
    return;
  }

  // Cria e lê a struct do cabeçalho
  if (!data_header_read(f_bin, &header)) {
    file_processing_failure_update(&f_bin);
    return;
  }

  // Lê o número de atualizações a serem feitas
  int num_updates;
  if (scanf("%d", &num_updates) != 1) {
    file_processing_failure_update(&f_bin);
    return;
  }

  // Itera sobre as sessões de atualização
  for (int i = 0; i < num_updates; i++) {
    DataRecord filter = {0};
    DataRecord updated = {0};
    // 1. Prepara o filtro (WHERE)
    bool search_for[PUBLIC_FIELDS];
    filter_build(&filter, search_for);

    // 2. Prepara os novos dados (SET)
    bool update_fields[PUBLIC_FIELDS];
    filter_build(&updated, update_fields);

    // 3. Aplica a atualização
    update_loop(f_bin, &header, search_for, &filter, update_fields, &updated);
  }

  // Atualiza o número de estações e pares de estações (direto na memória RAM)
  update_statistics(f_bin, &header);

  // Grava o cabeçalho consolidado e marca o arquivo como consistente
  header.status = '1';
  data_header_write(f_bin, &header);

  // Fecha o arquivo e libera a memória restante
  fclose(f_bin);

  // Imprime o hash final conforme correção
  BinarioNaTela(bin_name);
}
