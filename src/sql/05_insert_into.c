#include <stdbool.h>
#include <stdio.h>

#include "../../include/IO.h"
#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include "../../include/sql_functions.h"
#include "../../include/tools.h"

/**
 * @brief Função auxiliar para evitar repetição quando há falha no
 * processamento. Libera a memória alocada no heap e fecha o ponteiro do arquivo
 * binário.
 */
void file_processing_failure_insert(FILE **f_bin, DataHeader **header,
                                    DataRecord **record) {
  if (f_bin != NULL && *f_bin != NULL) {
    fclose(*f_bin);
    *f_bin = NULL;
  }
  if (header != NULL) {
    data_header_destroy(header);
  }
  if (record != NULL) {
    data_record_destroy(record);
  }

  printf("Falha no processamento do arquivo.\n");
}

/**
 * @brief Lê um novo registro da entrada padrão e realiza a inserção física no
 * arquivo. Se a pilha dinâmica de removidos estiver vazia, insere no fim
 * (proxRRN). Caso contrário, reaproveita o espaço do registro no topo da pilha.
 */
void insert_record(FILE *f_bin, DataHeader *header, DataRecord *record) {
  if (f_bin == NULL || header == NULL || record == NULL)
    return;

  // Lê os valores do novo registro a ser inserido usando a função de IO
  read_data_record_from_stdin(record);

  // Inicializa os campos removido e próximo
  data_record_set_removido(record, '0');
  data_record_set_proximo(record, -1);

  int current_topo = data_header_get_topo(header);

  // Se a pilha de removidos estiver vazia, insere o novo registro no final do
  // arquivo
  if (current_topo == -1) {
    int current_rrn = data_header_get_proxRRN(header);

    // Vai para o offset do registro de RRN == proxRRN e escreve
    fseek(f_bin, HEADER_SIZE + (current_rrn * RECORD_SIZE), SEEK_SET);
    data_record_write(f_bin, record);

    // Atualiza o próximo RRN na estrutura em memória
    data_header_set_proxRRN(header, current_rrn + 1);
  }
  // Se a pilha não estiver vazia, insere reaproveitando o espaço do RRN == topo
  else {
    int next_topo = -1;

    // Vai para o RRN do topo atual e pula 1 byte (campo char 'removido') para
    // acessar o campo 'proximo'
    fseek(f_bin, HEADER_SIZE + (current_topo * RECORD_SIZE) + 1, SEEK_SET);

    // Lê o campo 'proximo' para saber qual será o novo topo da pilha de lixo
    if (fread(&next_topo, sizeof(int), 1, f_bin) != 1) {
      return;
    }

    // Vai para o início físico do registro do topo e sobrescreve ele com os
    // dados novos
    fseek(f_bin, HEADER_SIZE + (current_topo * RECORD_SIZE), SEEK_SET);
    data_record_write(f_bin, record);

    // Atualiza o topo na estrutura do cabeçalho
    data_header_set_topo(header, next_topo);
  }
}

/**
 * @brief Executa a funcionalidade equivalente a um "INSERT INTO" em SQL.
 * Processa as entradas, realiza inserções (reaproveitando espaços via pilha)
 * e atualiza o número de estações/pares no final.
 */
void insert_into() {
  FILE *f_bin = NULL;
  DataHeader *header = NULL;
  DataRecord *record = NULL;

  // Lê o nome do arquivo binário
  char bin_name[50];
  if (scanf("%s", bin_name) != 1) {
    file_processing_failure_insert(&f_bin, &header, &record);
    return;
  }

  // Abre o arquivo .bin para leitura e escrita (rb+) e confere o status
  f_bin = open_binary_file(bin_name, "rb+");
  if (f_bin == NULL) {
    return; // A função de abertura já lida com prints e close
  }

  // Marca o arquivo como inconsistente durante as alterações
  mark_file_inconsistent(f_bin);

  // Instancia e lê os dados do cabeçalho
  header = data_header_create();
  if (header == NULL || !data_header_read(f_bin, header)) {
    file_processing_failure_insert(&f_bin, &header, &record);
    return;
  }

  // Lê o número de inserções a serem feitas
  int num_inserts;
  if (scanf("%d", &num_inserts) != 1) {
    file_processing_failure_insert(&f_bin, &header, &record);
    return;
  }

  // Loop para ler os registros e processar cada um
  for (int i = 0; i < num_inserts; i++) {
    // Aloca a struct de registro auxiliar para este loop
    record = data_record_create();
    if (record == NULL) {
      file_processing_failure_insert(&f_bin, &header, &record);
      return;
    }

    insert_record(f_bin, header, record);

    // Limpa a memória para garantir que o próximo loop crie um TAD zerado
    data_record_destroy(&record);
  }

  // Atualiza o número de estações e pares diretamente no cabeçalho em memória
  update_statistics(f_bin, header);

  // Marca como consistente e aplica todas as mudanças no disco de uma só vez
  data_header_set_status(header, '1');
  data_header_write(f_bin, header);

  // Fecha o arquivo binário e libera a memória
  fclose(f_bin);
  data_header_destroy(&header);

  // Imprime o hash final conforme correção
  BinarioNaTela(bin_name);
}
