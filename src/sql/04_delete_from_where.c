#include <stdbool.h>
#include <stdio.h>

#include "../../include/IO.h"
#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include "../../include/filtro.h"
#include "../../include/sql_functions.h"
#include "../../include/tools.h"

// Função auxiliar para evitar repetição quando há falha no processamento
// do arquivo. Libera memória, fecha o arquivo se estiver aberto e imprime a
// mensagem de erro.
void file_processing_failure_delete(FILE **f_bin) {
  if (f_bin != NULL && *f_bin != NULL) {
    fclose(*f_bin);
    *f_bin = NULL;
  }

  printf("Falha no processamento do arquivo.\n");
}

// Itera sobre os registros do arquivo e aplica a remoção lógica naqueles
// que baterem com o filtro. Atualiza o registro, marca como removido e gerencia
// a pilha dinâmica no cabeçalho.
void delete_loop(FILE *f_bin, DataHeader *header, bool *search_for,
                 DataRecord *filter) {
  if (f_bin == NULL || header == NULL || search_for == NULL || filter == NULL)
    return;

  // Instancia um registro auxiliar para iterar pelo arquivo binário
  DataRecord record;

  int max_records = header->proxRRN;

  // Itera pelos registros do .bin
  for (int rrn = 0; rrn < max_records; rrn++) {
    // Posiciona o ponteiro e lê o registro atual
    fseek(f_bin, HEADER_SIZE + (rrn * RECORD_SIZE), SEEK_SET);
    if (!data_record_read(f_bin, &record)) {
      break;
    }

    // Se o registro já está removido, ele é pulado
    if (record.removido == '1')
      continue;

    // Verifica se o registro bate com o filtro. Se bater, faz a remoção lógica.
    if (match_filter(&record, search_for, filter)) {
      // Remoção lógica em memória
      record.removido = '1';

      // Atribui ao campo próximo do registro o valor anterior do topo da pilha
      record.proximo = header->topo;

      // Atualiza o topo da pilha de registros removidos no cabeçalho em memória
      header->topo = rrn;

      // Volta o ponteiro do arquivo para reescrever o registro atualizado
      // (remoção lógica no disco)
      fseek(f_bin, HEADER_SIZE + (rrn * RECORD_SIZE), SEEK_SET);
      data_record_write(f_bin, &record);
    }

    // Se tiver o mesmo 'codEstacao' do filtro, encerra a busca
    if (match_codEstacao(&record, search_for, filter))
      break;
  }
}

// Faz a remoção lógica dos registros que batem com o filtro da consulta
void delete_from_where() {
  FILE *f_bin = NULL;
  DataHeader header;
  DataRecord filter;

  // Lê o nome do arquivo binário
  char bin_name[50];
  if (scanf("%s", bin_name) != 1) {
    file_processing_failure_delete(&f_bin);
    return;
  }

  // Abre o arquivo .bin para leitura e escrita (rb+), verifica consistência e
  // marca como inconsistente o status
  f_bin = open_binary_file(bin_name, "rb+");
  if (f_bin == NULL) {
    file_processing_failure_delete(&f_bin);
    return;
  }

  // Instancia e carrega o cabeçalho
  if (!data_header_read(f_bin, &header)) {
    file_processing_failure_delete(&f_bin);
    return;
  }

  // Lê o número de sessões de deleção a serem feitas
  int num_queries;
  if (scanf("%d", &num_queries) != 1) {
    file_processing_failure_delete(&f_bin);
    return;
  }

  // Itera sobre as sessões de deleção
  for (int i = 0; i < num_queries; i++) {
    // Array auxiliar para informar quais campos devem ser pesquisados
    bool search_for[PUBLIC_FIELDS];

    // Preenche a struct filter e o array search com os valores do filtro
    filter_build(&filter, search_for);

    delete_loop(f_bin, &header, search_for, &filter);
  }

  // Atualiza o número de estações e pares de estações diretamente no cabeçalho
  // em memória
  update_statistics(f_bin, &header);

  // Marca o arquivo como consistente após todas as remoções e atualizações
  header.status = '1';

  // Faz uma única gravação final no disco contendo o topo atualizado, as novas
  // estatísticas e o status consistente
  data_header_write(f_bin, &header);

  // Fecha o arquivo binário com segurança
  fclose(f_bin);

  BinarioNaTela(bin_name);
}
