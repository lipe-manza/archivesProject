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

/**
 * @brief Libera os TADs e fecha os arquivos de forma segura.
 */
static void cleanup_resources(FILE **f_data, FILE **f_btree, DataHeader **dh,
                              BTreeHeader **bth, DataRecord **filter,
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
}

/**
 * @brief Executa a remoção física de um registro de dados, atualizando a pilha
 * de removidos no cabeçalho do arquivo de dados.
 */
static void perform_data_deletion(FILE *f_data, DataHeader *cab_dados,
                                  DataRecord *registro, int rrn) {
  // 1. Marca como removido e aponta para o antigo topo
  data_record_set_removido(registro, '1');
  data_record_set_proximo(registro, data_header_get_topo(cab_dados));

  // 2. Atualiza o topo do cabeçalho
  data_header_set_topo(cab_dados, rrn);

  // 3. Persiste a alteração física no disco de dados
  long offset = DATA_HEADER_SIZE + (long)(rrn * DATA_RECORD_SIZE);
  fseek(f_data, offset, SEEK_SET);
  data_record_write(f_data, registro);
}

/**
 * @brief Funcionalidade [10]: Remove registros baseados em um filtro.
 * Orquestra a deleção encadeada no arquivo de dados e o rebalanceamento no
 * índice.
 */
void delete_from_where_ab() {
  char input_filename[50];
  char btree_filename[50];
  int n_queries;

  // Leitura padronizada: nome_dados, nome_indice, num_buscas
  if (scanf("%s %s %d", input_filename, btree_filename, &n_queries) != 3)
    return;

  FILE *f_data = fopen(input_filename, "rb+");
  FILE *f_btree = fopen(btree_filename, "rb+");

  if (!f_data || !f_btree) {
    printf("Falha no processamento do arquivo.\n");
    cleanup_resources(&f_data, &f_btree, NULL, NULL, NULL, NULL);
    return;
  }

  DataHeader *cab_dados = data_header_create();
  BTreeHeader *cab_btree = btree_header_create();
  DataRecord *filter = data_record_create();
  DataRecord *registro = data_record_create();

  if (!data_header_read(f_data, cab_dados) ||
      !btree_header_read(f_btree, cab_btree) ||
      data_header_get_status(cab_dados) == '0' ||
      btree_header_get_status(cab_btree) == '0') {
    printf("Falha no processamento do arquivo.\n");
    cleanup_resources(&f_data, &f_btree, &cab_dados, &cab_btree, &filter,
                      &registro);
    return;
  }

  // Trava de segurança (Crash Recovery)
  data_header_set_status(cab_dados, '0');
  btree_header_set_status(cab_btree, '0');
  data_header_write(f_data, cab_dados);
  btree_header_write(f_btree, cab_btree);

  for (int i = 0; i < n_queries; i++) {
    bool search_for[PUBLIC_FIELDS] = {false};
    filter_build(filter, search_for); // Preenche struct com dados do stdin

    // ESTRATÉGIA 1: O(log n) via Árvore-B se Chave Primária informada
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
            printf("DELETING KEY %d\n", target_key);
          }
        }
      }
    }
    // ESTRATÉGIA 2: O(n) Full Table Scan se não há Chave Primária
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
            printf("DELETING KEY %d\n", key_to_remove);
          }
        }
      }
    }
  }

  // Libera a trava (Consistência reestabelecida)
  data_header_set_status(cab_dados, '1');
  btree_header_set_status(cab_btree, '1');

  update_statistics(f_data, cab_dados);

  // Persiste cabeçalhos para o disco
  data_header_write(f_data, cab_dados);
  btree_header_write(f_btree, cab_btree);

  // Limpeza de heap e ponteiros
  cleanup_resources(&f_data, &f_btree, &cab_dados, &cab_btree, &filter,
                    &registro);

  // Validação run.codes
  BinarioNaTela(input_filename);
  BinarioNaTela(btree_filename);
}
