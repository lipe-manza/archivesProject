#include <stdbool.h>
#include <stdio.h>

#include "../../headers/IO.h"
#include "../../headers/sql_functions.h"

void select_from() {
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

  // Struct registro auxiliar para ler o .bin
  REG registro;

  // Flag para indicar se algum registro foi encontrado
  bool encontrou = false;

  // Pular para o primeiro registro
  fseek(f_bin, TAM_CABECALHO, SEEK_SET);

  // Itera pelos registros do .bin
  for (int RRN = 0; RRN < reg_count; RRN++) {
    // Lê o registro do .bin para a struct registro
    if (!read_from_bin(f_bin, &registro)) {
      printf("Falha na leitura do arquivo");
      fclose(f_bin);
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
