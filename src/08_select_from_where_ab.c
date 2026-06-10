#include <stdbool.h>
#include <stdio.h>

#include "../headers/IO.h"
#include "../headers/filtro.h"
#include "../headers/sql_functions.h"

// Função auxiliar para fechar os arquivos
void close_files(FILE *f_entrada, FILE *f_arvore_b) {
  if (f_entrada)
    fclose(f_entrada);
  if (f_arvore_b)
    fclose(f_arvore_b);
}

void select_from_where() {
  // Lê o nome do arquivo binário de entrada e da árvore B
  char nome_entrada[50];
  char nome_arvore_b[50];

  if (scanf("%s %s", nome_entrada, nome_arvore_b) != 2) {
    printf("Falha na leitura dos nomes do arquivos.\n");
    return;
  }

  // Abre o arquivo binário de entrada para leitura e verifica se a abertura
  // foi bem sucedida conferindo o status do arquivo
  FILE *f_entrada = open_bin(nome_entrada, "rb");
  if (f_entrada == NULL)
    return;

  // Vai para o campo proxRRN do registro de cabeçalho para ler quantos
  // registros existem
  int reg_count = 0;
  fseek(f_entrada, POS_PROX_RRN, SEEK_SET);
  if (fread(&reg_count, sizeof(int), 1, f_entrada) != 1) {
    printf("Falha no processamento do arquivo.\n");
    fclose(f_entrada);
    return;
  }

  // Lê o número de consultas a serem feitas
  int n;
  if (scanf("%d", &n) != 1) {
    printf("Entrada inválida.\n");
    fclose(f_entrada);
    return;
  }

  // Itera sobre as consultas
  for (int i = 0; i < n; i++) {
    // Struct registro que serve como comparação para filtrar os registros do
    // arquivo de entrada
    REG filter;

    // Array auxiliar para informar quais campos devem ser pesquisados e
    // comparados com o filtro
    bool search_for[PUBLIC_FIELDS];

    // Preenche a struct filter com os valores do filtro de pesquisa
    // e o array search com os campos a serem comparados
    filter_build(&filter, search_for);

    // Flag para indicar se algum registro foi encontrado
    bool encontrou = false;

    // Se um dos campos de busca for o codEstacao, usamos a árvore B
    if (search_for[0]) {
      // Abre o arquivo binário da árvore B para leitura e verifica se a
      // abertura foi bem sucedida conferindo o status do arquivo
      FILE *f_arvore_b = open_bin(nome_arvore_b, "rb");
      if (f_arvore_b == NULL) {
        fclose(f_entrada);
        return;
      }

      int RRN = 0; // TROCAR PELO DA ARVORE B

      REG registro;

      // Lê o registro do arquivo binário
      read_from_bin(f_entrada, &registro);

      // Se o registro passa pelo filtro ele é impresso
      if (match_filter(&registro, search_for, &filter)) {
        encontrou = true;
        print_registro_in_terminal(&registro);
      }
      fclose(f_arvore_b);
      f_arvore_b = NULL;
    } else {
      encontrou = search(f_entrada, reg_count, search_for, &filter);
    }

    // Se nenhum registro foi encontrado, o usuário é avisado
    if (!encontrou) {
      printf("Registro inexistente.\n");
    }

    // Separa as consultas por uma linha em branco
    printf("\n");
  }

  // Fecha o arquivo de entrada
  fclose(f_entrada);
  f_entrada = NULL;
}
