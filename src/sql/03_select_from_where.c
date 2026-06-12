#include "../../headers/IO.h"
#include "../../headers/filtro.h"
#include "../../headers/sql_functions.h"

// Função auxiliar para evitar repetição quando há falha no processamento do
// arquivo
void falha_processamento_arquivo(FILE **f) {
  if (f != NULL && *f != NULL) {
    fclose(*f);
    *f = NULL;
  }

  printf("Falha no processamento do arquivo.");
}

bool search(FILE *f_bin, CAB *cabecalho, bool *search_for, REG *filter) {
  if (f_bin == NULL || cabecalho == NULL || search_for == NULL ||
      filter == NULL)
    return false;

  // Struct registro auxiliar para ler o .bin
  REG registro;

  bool encontrou = false;

  // Pula para o primeiro Registro
  fseek(f_bin, TAM_CABECALHO, SEEK_SET);

  // Itera pelos registros do .bin
  for (int RRN = 0; RRN < cabecalho->proxRRN; RRN++) {
    // Lê o registro do arquivo binário
    ler_reg_bin(f_bin, &registro);
    // Se o registro está removido ele não é selecionado
    if (registro.removido == '1')
      continue;

    // Se o registro passa pelo filtro ele é impresso
    if (match_filter(&registro, search_for, filter)) {
      encontrou = true;
      print_registro_in_terminal(&registro);

      // Se achou o codEstacao acaba porque é chave única
      if (search_for[COD_ESTACAO])
        break;
    }
  }
  return encontrou;
}

void select_from_where() {
  FILE *f_bin = NULL;

  // Lê o nome do arquivo binário
  char bin_name[50];
  if (scanf("%s", bin_name) != 1) {
    falha_processamento_arquivo(&f_bin);
    return;
  }

  // Abre o arquivo .bin para leitura e verifica se a abertura
  // foi bem sucedida conferindo o status do arquivo
  f_bin = open_bin(bin_name, "rb");
  if (f_bin == NULL) {
    falha_processamento_arquivo(&f_bin);
    return;
  }

  // Cria a struct do cabeçalho lendo do arquivo binário
  CAB cabecalho;
  ler_cab_bin(f_bin, &cabecalho);

  // Lê o número de consultas a serem feitas
  int n;
  if (scanf("%d", &n) != 1) {
    falha_processamento_arquivo(&f_bin);
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

    bool encontrou = search(f_bin, &cabecalho, search_for, &filter);

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
