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
static void
file_processing_failure_select_bt(FILE **f_entrada, FILE **f_arvore_b,
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

  printf("Falha no processamento do arquivo.\n");
}

// Busca registros no arquivo de dados utilizando o
// índice Árvore-B quando o codEstacao for informado.
void select_from_where_ab() {
  char nome_entrada[50];
  char nome_arvore_b[50];

  // Lê os nomes dos arquivos
  if (scanf("%s %s", nome_entrada, nome_arvore_b) != 2)
    return;

  // Abre o arquivo .bin para leitura e verifica se a abertura
  // foi bem sucedida conferindo o status do arquivo
  FILE *f_entrada = open_binary_file(nome_entrada, "rb");
  if (f_entrada == NULL) {
    file_processing_failure_select_bt(NULL, NULL, NULL, NULL, NULL, NULL);
    return;
  }

  // Abre o arquivo .bin para leitura e verifica se a abertura
  // foi bem sucedida conferindo o status do arquivo
  FILE *f_arvore_b = open_binary_file(nome_arvore_b, "rb");
  if (f_arvore_b == NULL) {
    file_processing_failure_select_bt(&f_entrada, NULL, NULL, NULL, NULL, NULL);
    return;
  }

  // Instancia os TADs necessários
  DataHeader *cab_dados = data_header_create();
  BTreeHeader *cab_btree = btree_header_create();
  DataRecord *filter = data_record_create();
  DataRecord *registro = data_record_create();

  // Le os cabecalhos dos arquivos
  if (!data_header_read(f_entrada, cab_dados) ||
      !btree_header_read(f_arvore_b, cab_btree)) {
    file_processing_failure_select_bt(&f_entrada, &f_arvore_b, &cab_dados,
                                      &cab_btree, &filter, &registro);
    return;
  }

  int n_queries;
  if (scanf("%d", &n_queries) != 1) {
    file_processing_failure_select_bt(&f_entrada, &f_arvore_b, &cab_dados,
                                      &cab_btree, &filter, &registro);
    return;
  }

  // Processa cada uma das N buscas
  for (int i = 0; i < n_queries; i++) {
    // Inicializa o vetor search_for que possui quais campos serão buscados
    bool search_for[PUBLIC_FIELDS] = {false};

    // Constrói o filtro com base na entrada do usuário (Stdin)
    filter_build(filter, search_for);

    bool encontrou = false;

    // Verifica se o campo indexado (codEstacao mapeado para índice 0 no
    // filtro.h) foi solicitado
    // Se sim faz busca binária pela B-tree para achar o byteoffset do registro
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
            // Confirma se ele bate com os outros campos usando o filter
            if (match_filter(registro, search_for, filter)) {
              display_data_record(registro); // Printa  o registro
              printf("\n");
              encontrou = true;
            }
          }
        }
      }
    }
    // Quando a chave primária não foi informada na consulta
    // Buca sequencialmente pelo registro de dados (data_record)
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

  // Fecha arquivos e limpa a memória

  fclose(f_entrada);
  f_entrada = NULL;
  fclose(f_arvore_b);
  f_arvore_b = NULL;

  data_header_destroy(&cab_dados);
  btree_header_destroy(&cab_btree);
  data_record_destroy(&registro);
  data_record_destroy(&filter);
}
