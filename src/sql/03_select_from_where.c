#include <stdbool.h>
#include <stdio.h>

#include "../../include/IO.h"
#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include "../../include/filtro.h"
#include "../../include/sql_functions.h"

// Função auxiliar para evitar repetição quando há falha no processamento.
// Fecha os arquivos
void file_processing_failure_where(FILE **f_bin) {
  if (f_bin != NULL && *f_bin != NULL) {
    fclose(*f_bin);
    *f_bin = NULL;
  }

  printf("Falha no processamento do arquivo.\n");
}

// Itera pelos registros do arquivo binário e imprime aqueles que passam
// pelo filtro.
bool search(FILE *f_bin, DataHeader *header, bool *search_for,
            DataRecord *filter) {
  if (f_bin == NULL || header == NULL || search_for == NULL || filter == NULL)
    return false;

  // Instancia um registro auxiliar para ler os dados do disco
  DataRecord record;

  bool found = false;

  // Pula o cabeçalho e vai para o primeiro Registro
  fseek(f_bin, HEADER_SIZE, SEEK_SET);

  int max_records = header->proxRRN;

  // Itera pelos registros do .bin
  for (int rrn = 0; rrn < max_records; rrn++) {
    // Lê o registro do arquivo binário
    if (!data_record_read(f_bin, &record)) {
      break;
    }

    // Se o registro está removido, ele não é selecionado
    if (record.removido == '1')
      continue;

    // Se o registro passa pelo filtro, ele é impresso
    if (match_filter(&record, search_for, filter)) {
      found = true;
      display_data_record(&record);
    }
    // Se tiver o mesmo 'codEstacao' do filtro, encerra a busca
    if (match_codEstacao(&record, search_for, filter))
      break;
  }

  return found;
}

// Imprime apenas os registros não removidos que passam pelo filtro
void select_from_where() {
  FILE *f_bin = NULL;
  DataHeader header;
  DataRecord filter;

  // Lê o nome do arquivo binário
  char bin_name[50];
  if (scanf("%s", bin_name) != 1) {
    file_processing_failure_where(&f_bin);
    return;
  }

  // Abre o arquivo .bin para leitura e verifica consistência
  f_bin = open_binary_file(bin_name, "rb");
  if (f_bin == NULL) {
    file_processing_failure_where(&f_bin);
    return;
  }

  // Cria a struct do cabeçalho lendo do arquivo binário
  if (!data_header_read(f_bin, &header)) {
    file_processing_failure_where(&f_bin);
    return;
  }

  // Lê o número de consultas a serem feitas
  int num_queries;
  if (scanf("%d", &num_queries) != 1) {
    file_processing_failure_where(&f_bin);
    return;
  }

  // Itera sobre as consultas
  for (int i = 0; i < num_queries; i++) {

    // Array auxiliar para informar quais campos devem ser comparados com o
    // filtro
    bool search_for[PUBLIC_FIELDS];

    // Preenche a struct filter com os valores do filtro de pesquisa
    filter_build(&filter, search_for);

    bool found = search(f_bin, &header, search_for, &filter);

    // Se nenhum registro foi encontrado, o usuário é avisado
    if (!found) {
      printf("Registro inexistente.\n");
    }

    // Separa as consultas por uma linha em branco
    printf("\n");
  }

  // Libera a memória final
  fclose(f_bin);
}
