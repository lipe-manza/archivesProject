#include <stdbool.h>
#include <stdio.h>

#include "../../include/IO.h"
#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include "../../include/filtro.h"
#include "../../include/sql_functions.h"
#include "../../include/tools.h"

/**
 * @brief Função auxiliar para evitar repetição quando há falha no processamento
 * do arquivo. Libera memória, fecha o arquivo se estiver aberto e imprime a
 * mensagem de erro.
 */
void file_processing_failure_delete(FILE **f_bin, DataHeader **header,
                                    DataRecord **filter) {
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

  printf("Falha no processamento do arquivo.\n");
}

/**
 * @brief Itera sobre os registros do arquivo e aplica a remoção lógica naqueles
 * que baterem com o filtro. Atualiza o registro, marca como removido e gerencia
 * a pilha dinâmica no cabeçalho.
 */
void delete_loop(FILE *f_bin, DataHeader *header, bool *search_for,
                 DataRecord *filter) {
  if (f_bin == NULL || header == NULL || search_for == NULL || filter == NULL)
    return;

  // Instancia um registro auxiliar para iterar pelo arquivo binário
  DataRecord *record = data_record_create();
  if (record == NULL)
    return;

  int max_records = data_header_get_proxRRN(header);

  // Itera pelos registros do .bin
  for (int rrn = 0; rrn < max_records; rrn++) {
    // Posiciona o ponteiro e lê o registro atual
    fseek(f_bin, HEADER_SIZE + (rrn * RECORD_SIZE), SEEK_SET);
    if (!data_record_read(f_bin, record)) {
      break;
    }

    // Se o registro já está removido, ele é pulado
    if (data_record_get_removido(record) == '1')
      continue;

    // Verifica se o registro bate com o filtro. Se bater, faz a remoção lógica.
    if (match_filter(record, search_for, filter)) {
      // Remoção lógica em memória
      data_record_set_removido(record, '1');

      // Atribui ao campo próximo do registro o valor anterior do topo da pilha
      data_record_set_proximo(record, data_header_get_topo(header));

      // Atualiza o topo da pilha de registros removidos no cabeçalho em memória
      data_header_set_topo(header, rrn);

      // Volta o ponteiro do arquivo para reescrever o registro atualizado
      // (remoção lógica no disco)
      fseek(f_bin, HEADER_SIZE + (rrn * RECORD_SIZE), SEEK_SET);
      data_record_write(f_bin, record);
    }
  }

  // Libera a memória do registro auxiliar
  data_record_destroy(&record);
}

/**
 * @brief Executa a funcionalidade equivalente a um "DELETE FROM ... WHERE" em
 * SQL. Gerencia a abertura em modo rb+, loops de filtragem e atualização da
 * pilha de removidos.
 */
void delete_from_where() {
  FILE *f_bin = NULL;
  DataHeader *header = NULL;
  DataRecord *filter = NULL;

  // Lê o nome do arquivo binário
  char bin_name[50];
  if (scanf("%s", bin_name) != 1) {
    file_processing_failure_delete(&f_bin, &header, &filter);
    return;
  }

  // Abre o arquivo .bin para leitura e escrita (rb+) e verifica consistência
  f_bin = open_binary_file(bin_name, "rb+");
  if (f_bin == NULL) {
    // open_binary_file já imprime o erro e realiza o close apropriado
    return;
  }

  // Marca o arquivo como inconsistente durante o processo de alteração
  mark_file_inconsistent(f_bin);

  // Instancia e carrega o cabeçalho
  header = data_header_create();
  if (header == NULL || !data_header_read(f_bin, header)) {
    file_processing_failure_delete(&f_bin, &header, &filter);
    return;
  }

  // Lê o número de sessões de deleção a serem feitas
  int num_queries;
  if (scanf("%d", &num_queries) != 1) {
    file_processing_failure_delete(&f_bin, &header, &filter);
    return;
  }

  // Itera sobre as sessões de deleção
  for (int i = 0; i < num_queries; i++) {
    filter = data_record_create();
    if (filter == NULL) {
      file_processing_failure_delete(&f_bin, &header, &filter);
      return;
    }

    // Array auxiliar para informar quais campos devem ser pesquisados
    bool search_for[PUBLIC_FIELDS];

    // Preenche a struct filter e o array search com os valores do filtro
    filter_build(filter, search_for);

    delete_loop(f_bin, header, search_for, filter);

    // Destrói o filtro para a próxima iteração
    data_record_destroy(&filter);
  }

  // Atualiza o número de estações e pares de estações diretamente no cabeçalho
  // em memória
  update_statistics(f_bin, header);

  // Marca o arquivo como consistente após todas as remoções e atualizações
  data_header_set_status(header, '1');

  // Faz uma única gravação final no disco contendo o topo atualizado, as novas
  // estatísticas e o status consistente
  data_header_write(f_bin, header);

  // Fecha o arquivo binário com segurança e libera a memória do TAD
  fclose(f_bin);
  data_header_destroy(&header);

  // Imprime o binário na tela conforme especificado no trabalho prático
  BinarioNaTela(bin_name);
}
