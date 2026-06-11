#include <stdbool.h>
#include <stdio.h>

#include "../../headers/IO.h"
#include "../../headers/filtro.h"
#include "../../headers/sql_functions.h"

bool search(FILE *f_bin, int reg_count, bool *search_for, REG *filter) {
  // Struct registro auxiliar para ler o .bin
  REG registro;

  // Pula para o primeiro Registro
  fseek(f_bin, TAM_CABECALHO, SEEK_SET);

  // Itera pelos registros do .bin
  for (int RRN = 0; RRN < reg_count; RRN++) {
    // Lê o registro do arquivo binário
    read_from_bin(f_bin, &registro);
    // Se o registro está removido ele não é selecionado
    if (registro.removido == '1')
      continue;

    // Se o registro passa pelo filtro ele é impresso
    if (match_filter(&registro, search_for, filter)) {
      return true;
      print_registro_in_terminal(&registro);

      // Se achou o codEst acaba porque é chave única
      if (search_for[0])
        break;
    }
  }
  return false;
}

void select_from_where() {
  char bin_name[50];
  // Lê o nome do arquivo binário
  if (scanf("%s", bin_name) != 1) {
    printf("Falha na leitura do nome do arquivo.\n");
    return;
  }

  // Abre o arquivo .bin para leitura e verifica se a abertura
  // foi bem sucedida conferindo o status do arquivo
  FILE *f_bin = open_bin(bin_name, "rb");
  if (f_bin == NULL)
    return;

  // Vai para o campo proxRRN do registro de cabeçalho para ler quantos
  // registros existem
  int reg_count = 0;
  fseek(f_bin, POS_PROX_RRN, SEEK_SET);
  if (fread(&reg_count, sizeof(int), 1, f_bin) != 1) {
    printf("Falha no processamento do arquivo.\n");
    fclose(f_bin);
    return;
  }

  // Lê o número de consultas a serem feitas
  int n;
  if (scanf("%d", &n) != 1) {
    printf("Entrada inválida.\n");
    fclose(f_bin);
    return;
  }

  // Itera sobre as consultas
  for (int i = 0; i < n; i++) {
    // Struct registro que serve como comparação para filtrar
    // os registros do arquivo .bin
    REG filter;

    // Array auxiliar para informar quais campos devem ser pesquisados e
    // comparados com o filtro
    bool search_for[PUBLIC_FIELDS];

    // Preenche a struct filter com os valores do filtro de pesquisa
    // e o array search com os campos a serem comparados
    filter_build(&filter, search_for);

    bool encontrou = search(f_bin, reg_count, search_for, &filter);

    // Se nenhum registro foi encontrado, o usuário é avisado
    if (!encontrou) {
      printf("Registro inexistente.\n");
    }

    // Separa as consultas por uma linha em branco
    printf("\n");
  }

  // Fecha o arquivo .bin
  fclose(f_bin);
  f_bin = NULL;
}
