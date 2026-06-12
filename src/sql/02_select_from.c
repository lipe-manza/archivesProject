#include "../../headers/IO.h"
#include "../../headers/registro.h"
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

void select_from() {
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

  // Struct registro auxiliar para ler o .bin
  REG registro;

  // Flag para indicar se algum registro foi encontrado
  bool encontrou = false;

  // Pular para o primeiro registro
  fseek(f_bin, TAM_CABECALHO, SEEK_SET);

  // Itera pelos registros do .bin
  for (int RRN = 0; RRN < cabecalho.proxRRN; RRN++) {
    // Lê o registro do .bin para a struct registro
    if (!ler_reg_bin(f_bin, &registro)) {
      falha_processamento_arquivo(&f_bin);
      return;
    };

    // O registro só é impresso se não estiver removido
    if (registro.removido == '0') {
      encontrou = true;
      print_registro_in_terminal(&registro);
    }
  }

  // Se nenhum registro foi encontrado, o usuário é avisado
  if (!encontrou) {
    printf("Registro inexistente.\n");
  }

  // Fecha o arquivo .bin
  fclose(f_bin);
  f_bin = NULL;
}
