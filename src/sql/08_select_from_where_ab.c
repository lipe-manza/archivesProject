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
file_processing_failure_select_bt(FILE **f_entrada, FILE **f_arvore_b) {
  if (f_entrada && *f_entrada) {
    fclose(*f_entrada);
    *f_entrada = NULL;
  }
  if (f_arvore_b && *f_arvore_b) {
    fclose(*f_arvore_b);
    *f_arvore_b = NULL;
  }

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
    file_processing_failure_select_bt(NULL, NULL);
    return;
  }

  // Abre o arquivo .bin para leitura e verifica se a abertura
  // foi bem sucedida conferindo o status do arquivo
  FILE *f_arvore_b = open_binary_file(nome_arvore_b, "rb");
  if (f_arvore_b == NULL) {
    file_processing_failure_select_bt(&f_entrada, NULL);
    return;
  }

  // Instancia as structs necessárias na stack
  DataHeader cab_dados = {0};
  BTreeHeader cab_btree = {0};
  DataRecord registro = {0};

  // Le os cabecalhos dos arquivos
  if (!data_header_read(f_entrada, &cab_dados) ||
      !btree_header_read(f_arvore_b, &cab_btree)) {
    file_processing_failure_select_bt(&f_entrada, &f_arvore_b);
    return;
  }

  int n_queries;
  if (scanf("%d", &n_queries) != 1) {
    file_processing_failure_select_bt(&f_entrada, &f_arvore_b);
    return;
  }

  // Processa cada uma das N buscas
  for (int i = 0; i < n_queries; i++) {
    DataRecord filter = {0};
    // Inicializa o vetor search_for que possui quais campos serão buscados
    bool search_for[PUBLIC_FIELDS] = {false};

    // Constrói o filtro com base na entrada do usuário (Stdin)
    filter_build(&filter, search_for);

    bool encontrou = false;

    // Verifica se o campo indexado (codEstacao mapeado para índice 0 no
    // filtro.h) foi solicitado
    // Se sim faz busca binária pela B-tree para achar o byteoffset do registro
    if (search_for[COD_ESTACAO]) {
      int search_key = filter.codEstacao;

      // Busca o byte offset no índice
      int offset = btree_search_key(f_arvore_b, &cab_btree, search_key);

      if (offset != BTREE_NOT_FOUND) {
        // Dá o salto direto no arquivo de dados
        fseek(f_entrada, offset, SEEK_SET);

        if (data_record_read(f_entrada, &registro)) {
          // Confirma se o registro não está logicamente removido
          if (registro.removido == '0') {
            // Confirma se ele bate com os outros campos usando o filter
            if (match_filter(&registro, search_for, &filter)) {
              display_data_record(&registro); // Printa  o registro
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
      int prox_rrn = cab_dados.proxRRN;
      fseek(f_entrada, DATA_HEADER_SIZE, SEEK_SET);

      for (int j = 0; j < prox_rrn; j++) {
        if (data_record_read(f_entrada, &registro)) {
          if (registro.removido == '0') {
            if (match_filter(&registro, search_for, &filter)) {
              display_data_record(&registro);
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
}
