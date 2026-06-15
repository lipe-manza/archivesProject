#include "../../include/IO.h"
#include "../../include/btree.h"
#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include "../../include/filtro.h"
#include "../../include/sql_functions.h"
#include "../../include/tools.h"
#include <stdio.h>
#include <stdlib.h>

#define DATA_HEADER_SIZE 17
#define DATA_RECORD_SIZE 80

// Fecha os arquivos de forma segura.
static void file_processing_failure_delete_bt(FILE **f_data, FILE **f_btree) {
  if (f_data && *f_data) {
    fclose(*f_data);
    *f_data = NULL;
  }
  if (f_btree && *f_btree) {
    fclose(*f_btree);
    *f_btree = NULL;
  }

  printf("Falha no processamento do arquivo.\n");
}

// Executa a remoção lógica de um registro de dados, atualizando a pilha de
// removidos no cabeçalho do arquivo de dados.
static void perform_data_deletion(FILE *f_data, DataHeader *cab_dados,
                                  DataRecord *registro, int rrn) {
  // Marca o registro como removido e faz o campo 'proxRRN' apontar para o
  // antigo topo
  registro->removido = '1';
  registro->proximo = cab_dados->topo;

  // Atualiza o topo do cabeçalho
  cab_dados->topo = rrn;

  // Grava as alterações do registro removido em disco
  long offset = DATA_HEADER_SIZE + (long)(rrn * DATA_RECORD_SIZE);
  fseek(f_data, offset, SEEK_SET);
  data_record_write(f_data, registro);
}

// Executa a remoção lógica dos registros que batem com o filtro e atualiza a
// árvore B
void delete_from_where_ab() {
  char input_filename[50];
  char btree_filename[50];
  int n_queries;

  // Lê os nomes do arquivo de entrada e da árvore B e o número de consultas
  if (scanf("%s %s %d", input_filename, btree_filename, &n_queries) != 3)
    return;

  // Abre os arquivos binários para escrita e leitura, confere a consistencia e
  // marca o status como inconsistentes
  FILE *f_data = open_binary_file(input_filename, "rb+");
  FILE *f_btree = open_binary_file(btree_filename, "rb+");

  // Confere se os arquivos foram abertos corretamente
  if (!f_data || !f_btree) {
    file_processing_failure_delete_bt(&f_data, &f_btree);
    return;
  }

  // Instancia as structs necessárias para as leituras dos cabeçalhos, registros e
  // nós dos arquivos binários na stack
  DataHeader cab_dados = {0};
  BTreeHeader cab_btree = {0};
  DataRecord filter = {0};
  DataRecord registro = {0};

  // Faz a leitura dos cabeçalhos dos arquivos binários
  if (!data_header_read(f_data, &cab_dados) ||
      !btree_header_read(f_btree, &cab_btree)) {
    file_processing_failure_delete_bt(&f_data, &f_btree);
    return;
  }

  // Itera sobre as consultas
  for (int i = 0; i < n_queries; i++) {
    bool search_for[PUBLIC_FIELDS] = {false};
    filter_build(&filter, search_for); // Preenche struct com dados do stdin

    // Caso 1: campo 'codEstacao', que é chave da árvore B, foi informado
    if (search_for[COD_ESTACAO]) {
      int target_key = filter.codEstacao;
      int offset = btree_search_key(f_btree, &cab_btree, target_key);

      if (offset != BTREE_NOT_FOUND) {
        int rrn = (offset - DATA_HEADER_SIZE) / DATA_RECORD_SIZE;
        fseek(f_data, offset, SEEK_SET);

        if (data_record_read(f_data, &registro) &&
            registro.removido == '0') {
          if (match_filter(&registro, search_for, &filter)) {
            // Deleção dupla (Dados + Índice)
            perform_data_deletion(f_data, &cab_dados, &registro, rrn);
            btree_delete_key(f_btree, &cab_btree, target_key);
          }
        }
      }
    }
    // Caso 2: remoção comum iterando por toda a tabela
    else {
      int prox_rrn = cab_dados.proxRRN;

      for (int rrn = 0; rrn < prox_rrn; rrn++) {
        fseek(f_data, DATA_HEADER_SIZE + (long)(rrn * DATA_RECORD_SIZE),
              SEEK_SET);

        if (data_record_read(f_data, &registro) &&
            registro.removido == '0') {
          if (match_filter(&registro, search_for, &filter)) {
            // Salva a chave antes de deletar do registro, pois precisaremos
            // dela para encontrar o nó na Árvore-B
            int key_to_remove = registro.codEstacao;

            // Deleção dupla
            perform_data_deletion(f_data, &cab_dados, &registro, rrn);
            btree_delete_key(f_btree, &cab_btree, key_to_remove);
          }
        }
      }
    }
  }

  // Atualiza a consistência do arquivo nas structs de cabeçalho
  cab_dados.status = '1';
  cab_btree.status = '1';

  // Atualiza o número de estações e número de pares de estações usando as
  // hashtables
  update_statistics(f_data, &cab_dados);

  // Escreve cabeçalhos no disco
  data_header_write(f_data, &cab_dados);
  btree_header_write(f_btree, &cab_btree);

  // Limpeza de heap e ponteiros
  fclose(f_data);
  f_data = NULL;
  fclose(f_btree);
  f_btree = NULL;

  BinarioNaTela(input_filename);
  BinarioNaTela(btree_filename);
}
