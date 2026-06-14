#include "../../include/IO.h"
#include "../../include/btree.h"
#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include "../../include/filtro.h"
#include "../../include/sql_functions.h"
#include <stdio.h>
#include <stdlib.h>

#define DATA_HEADER_SIZE 17

// Função auxiliar para fechar arquivos e limpar a memória de forma
// segura.
static void cleanup_resources(FILE **f_entrada, FILE **f_arvore_b,
                              DataHeader **dh, BTreeHeader **bth,
                              DataRecord **filter, DataRecord **reg) {
  if (f_entrada && *f_entrada) {
    fclose(*f_entrada);
    *f_entrada = NULL;
  }
  if (f_arvore_b && *f_arvore_b) {
    fclose(*f_arvore_b);
    *f_arvore_b = NULL;
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

// Funcionalidade [8]: Busca registros no arquivo de dados utilizando o
// índice Árvore-B quando o codEstacao for informado.
void select_from_where_ab() {
  char nome_entrada[50];
  char nome_arvore_b[50];

  // Lê os nomes dos arquivos
  if (scanf("%s %s", nome_entrada, nome_arvore_b) != 2)
    return;

  FILE *f_entrada = fopen(nome_entrada, "rb");
  if (f_entrada == NULL) {
    printf("Falha no processamento do arquivo.\n");
    return;
  }

  FILE *f_arvore_b = fopen(nome_arvore_b, "rb");
  if (f_arvore_b == NULL) {
    printf("Falha no processamento do arquivo.\n");
    cleanup_resources(&f_entrada, NULL, NULL, NULL, NULL, NULL);
    return;
  }

  // Instancia os TADs necessários
  DataHeader *cab_dados = data_header_create();
  BTreeHeader *cab_btree = btree_header_create();
  DataRecord *filter = data_record_create();
  DataRecord *registro = data_record_create();

  // Lê e valida a consistência de ambos os cabeçalhos
  if (!data_header_read(f_entrada, cab_dados) ||
      !btree_header_read(f_arvore_b, cab_btree)) {
    printf("Falha no processamento do arquivo.\n");
    cleanup_resources(&f_entrada, &f_arvore_b, &cab_dados, &cab_btree, &filter,
                      &registro);
    return;
  }

  if (data_header_get_status(cab_dados) == '0' ||
      btree_header_get_status(cab_btree) == '0') {
    printf("Falha no processamento do arquivo.\n");
    cleanup_resources(&f_entrada, &f_arvore_b, &cab_dados, &cab_btree, &filter,
                      &registro);
    return;
  }

  int n_queries;
  if (scanf("%d", &n_queries) != 1) {
    cleanup_resources(&f_entrada, &f_arvore_b, &cab_dados, &cab_btree, &filter,
                      &registro);
    return;
  }

  // Processa cada uma das N buscas
  for (int i = 0; i < n_queries; i++) {
    bool search_for[PUBLIC_FIELDS] = {false};

    // Constrói o filtro com base na entrada do usuário (Stdin)
    filter_build(filter, search_for);

    bool encontrou = false;

    // ESTRATÉGIA 1: Busca Indexada via Árvore-B (O(log n))
    // Verifica se o campo indexado (codEstacao mapeado para índice 0 no
    // filtro.h) foi solicitado
    if (search_for[COD_ESTACAO]) {
      int search_key = data_record_get_codEstacao(filter);

      // Busca o byte offset no índice
      int offset = btree_search_key(f_arvore_b, cab_btree, search_key);

      if (offset != BTREE_NOT_FOUND) {
        // Dá o salto direto no arquivo de dados
        fseek(f_entrada, offset, SEEK_SET);

        if (data_record_read(f_entrada, registro)) {
          // Confirma se o registro não está logicamente removido
          if (data_record_get_removido(registro) == '0') {
            // Confirma se ele passa nos OUTROS critérios da cláusula WHERE
            if (match_filter(registro, search_for, filter)) {
              display_data_record(registro); // Função da IO.h
              printf("\n");
              encontrou = true;
            }
          }
        }
      }
    }
    // ESTRATÉGIA 2: Busca Sequencial (Full Table Scan O(n))
    // Quando a chave primária não foi informada na consulta
    else {
      int prox_rrn = data_header_get_proxRRN(cab_dados);
      fseek(f_entrada, DATA_HEADER_SIZE, SEEK_SET);

      for (int j = 0; j < prox_rrn; j++) {
        if (data_record_read(f_entrada, registro)) {
          if (data_record_get_removido(registro) == '0') {
            if (match_filter(registro, search_for, filter)) {
              display_data_record(registro);
              encontrou = true;
            }
          }
        }
      }
      printf("\n");
    }

    if (!encontrou) {
      printf("Registro inexistente.\n");
      printf("\n");
    }
  }

  cleanup_resources(&f_entrada, &f_arvore_b, &cab_dados, &cab_btree, &filter,
                    &registro);
}
