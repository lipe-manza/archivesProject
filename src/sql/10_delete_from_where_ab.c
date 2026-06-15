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

// Libera os TADs e fecha os arquivos de forma segura.
static void file_processing_failure_delete_bt(FILE **f_data, FILE **f_btree,
                                              DataHeader **dh,
                                              BTreeHeader **bth,
                                              DataRecord **filter,
                                              DataRecord **reg) {
  if (f_data && *f_data) {
    fclose(*f_data);
    *f_data = NULL;
  }
  if (f_btree && *f_btree) {
    fclose(*f_btree);
    *f_btree = NULL;
  }
  if (dh)
    data_header_destroy(dh);
  if (bth)
    btree_header_destroy(bth);
  if (filter)
    data_record_destroy(filter);
  if (reg)
    data_record_destroy(reg);

  printf("Falha no processamento do arquivo.\n");
}

// Executa a remoção lógica de um registro de dados, atualizando a pilha de
// removidos no cabeçalho do arquivo de dados.
static void perform_data_deletion(FILE *f_data, DataHeader *cab_dados,
                                  DataRecord *registro, int rrn) {
  // Marca o registro como removido e faz o campo 'proxRRN' apontar para o
  // antigo topo
  data_record_set_removido(registro, '1');
  data_record_set_proximo(registro, data_header_get_topo(cab_dados));

  // Atualiza o topo do cabeçalho
  data_header_set_topo(cab_dados, rrn);

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
    file_processing_failure_delete_bt(&f_data, &f_btree, NULL, NULL, NULL,
                                      NULL);
    return;
  }

  // Instancia os TADs necessários para a leituras dos cabeçalhos, registros e
  // nós dos arquivos binários
  DataHeader *cab_dados = data_header_create();
  BTreeHeader *cab_btree = btree_header_create();
  DataRecord *filter = data_record_create();
  DataRecord *registro = data_record_create();

  // Faz a leitura dos cabeçalhos dos arquivos binários
  if (!data_header_read(f_data, cab_dados) ||
      !btree_header_read(f_btree, cab_btree)) {
    file_processing_failure_delete_bt(&f_data, &f_btree, &cab_dados, &cab_btree,
                                      &filter, &registro);
    return;
  }

  // Itera sobre as consultas
  for (int i = 0; i < n_queries; i++) {
    bool search_for[PUBLIC_FIELDS] = {false};
    filter_build(filter, search_for); // Preenche struct com dados do stdin

    // Caso 1: campo 'codEstacao', que é chave da árvore B, foi informado
    if (search_for[COD_ESTACAO]) {
      int target_key = data_record_get_codEstacao(filter);
      int offset = btree_search_key(f_btree, cab_btree, target_key);

      if (offset != BTREE_NOT_FOUND) {
        int rrn = (offset - DATA_HEADER_SIZE) / DATA_RECORD_SIZE;
        fseek(f_data, offset, SEEK_SET);

        if (data_record_read(f_data, registro) &&
            data_record_get_removido(registro) == '0') {
          if (match_filter(registro, search_for, filter)) {
            // Deleção dupla (Dados + Índice)
            perform_data_deletion(f_data, cab_dados, registro, rrn);
            btree_delete_key(f_btree, cab_btree, target_key);
          }
        }
      }
    }
    // Caso 2: remoção comum iterando por toda a tabela
    else {
      int prox_rrn = data_header_get_proxRRN(cab_dados);

      for (int rrn = 0; rrn < prox_rrn; rrn++) {
        fseek(f_data, DATA_HEADER_SIZE + (long)(rrn * DATA_RECORD_SIZE),
              SEEK_SET);

        if (data_record_read(f_data, registro) &&
            data_record_get_removido(registro) == '0') {
          if (match_filter(registro, search_for, filter)) {
            // Salva a chave antes de deletar do registro, pois precisaremos
            // dela para encontrar o nó na Árvore-B
            int key_to_remove = data_record_get_codEstacao(registro);

            // Deleção dupla
            perform_data_deletion(f_data, cab_dados, registro, rrn);
            btree_delete_key(f_btree, cab_btree, key_to_remove);
          }
        }
      }
    }
  }

  // Atualiza a consistência do arquivo nas structs de cabeçalho
  data_header_set_status(cab_dados, '1');
  btree_header_set_status(cab_btree, '1');

  // Atualiza o número de estações e número de pares de estações usando as
  // hashtables
  update_statistics(f_data, cab_dados);

  // Escreve cabeçalhos no disco
  data_header_write(f_data, cab_dados);
  btree_header_write(f_btree, cab_btree);

  // Limpeza de heap e ponteiros
  fclose(f_data);
  f_data = NULL;
  fclose(f_btree);
  f_btree = NULL;
  data_header_destroy(&cab_dados);
  btree_header_destroy(&cab_btree);
  data_record_destroy(&filter);
  data_record_destroy(&registro);

  BinarioNaTela(input_filename);
  BinarioNaTela(btree_filename);
}
