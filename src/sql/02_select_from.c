#include <stdbool.h>
#include <stdio.h>

#include "../../include/IO.h"
#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include "../../include/sql_functions.h"

// Função auxiliar para evitar repetição de código quando há falha no
// processamento. Fecha arquivos abertos antes de exibir a mensagem de erro.
void file_processing_failure_select(FILE **f_bin) {
  if (f_bin != NULL && *f_bin != NULL) {
    fclose(*f_bin);
    *f_bin = NULL;
  }

  printf("Falha no processamento do arquivo.\n");
}

// Lê todos os registros do arquivo binário e imprime os que não estão
// logicamente removidos.
void select_from() {
  FILE *f_bin = NULL;
  DataHeader header;
  DataRecord record;

  // Lê o nome do arquivo binário
  char bin_name[50];
  if (scanf("%s", bin_name) != 1) {
    file_processing_failure_select(&f_bin);
    return;
  }

  // Abre o arquivo .bin para leitura e verifica se a abertura
  // foi bem sucedida conferindo o status do arquivo
  f_bin = open_binary_file(bin_name, "rb");
  if (f_bin == NULL) {
    file_processing_failure_select(&f_bin);
    return;
  }

  // Instancia e cria a estrutura do cabeçalho lendo do arquivo binário
  if (!data_header_read(f_bin, &header)) {
    file_processing_failure_select(&f_bin);
    return;
  }

  // Flag para indicar se algum registro foi encontrado e exibido
  bool found = false;

  // Pular para o primeiro registro físico (após o cabeçalho)
  fseek(f_bin, HEADER_SIZE, SEEK_SET);

  // Itera por todos os registros previstos no arquivo binário
  int total_records = header.proxRRN;
  for (int rrn = 0; rrn < total_records; rrn++) {

    // Lê o registro do .bin para a estrutura
    if (!data_record_read(f_bin, &record)) {
      file_processing_failure_select(&f_bin);
      printf("Record read\n");
      return;
    }

    // O registro só é impresso se não estiver marcado como removido
    if (record.removido == '0') {
      found = true;
      display_data_record(&record);
    }
  }

  // Se nenhum registro for encontrado (arquivo apenas com removidos), o usuário
  // é avisado
  if (!found) {
    printf("Registro inexistente.\n");
  }

  // Fecha o arquivo
  fclose(f_bin);
}
