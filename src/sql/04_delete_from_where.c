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

void delete_loop(FILE *f_bin, CAB *cabecalho, bool *search, REG *filter) {
  if (f_bin == NULL || cabecalho == NULL || search == NULL || filter == NULL)
    return;

  // Struct registro auxiliar para ler o binário
  REG registro;

  // Itera pelos registros do .bin
  for (int RRN = 0; RRN < cabecalho->proxRRN; RRN++) {
    // Lê o registro do .bin para a struct registro
    ler_reg_bin(f_bin, &registro);

    // Se o registro está removido ele é pulado
    if (registro.removido == '1')
      continue;

    // Verifica se o registro bate com o filtro, e se bater faz a
    // remoção lógica do registro
    if (match_filter(&registro, search, filter)) {
      // Remoção lógica

      char removido = '1';

      // Define o registro atual como removido
      fseek(f_bin, REG_BYTE_OFFSET(RRN) + POS_REM_REG, SEEK_SET);
      fwrite(&removido, sizeof(char), 1, f_bin);

      // Atribui ao campo próximo do registro o valor anterior do topo
      // da pilha de registros removidos
      fwrite(&cabecalho->topo, sizeof(int), 1, f_bin);

      cabecalho->topo = RRN;
    }
  }
}

void delete_from_where() {
  FILE *f_bin = NULL;

  // Lê o nome do arquivo binário
  char bin_name[50];
  if (scanf("%s", bin_name) != 1) {
    falha_processamento_arquivo(&f_bin);
    return;
  }

  // Abre o arquivo .bin para leitura e escrita e verifica se a abertura
  // foi bem sucedida conferindo o status do arquivo
  f_bin = open_bin(bin_name, "rb+");
  if (f_bin == NULL) {
    falha_processamento_arquivo(&f_bin);
    return;
  }

  tornar_inconsistente(f_bin);

  // Cria a struct do cabeçalho lendo do arquivo binário
  CAB cabecalho;
  ler_cab_bin(f_bin, &cabecalho);

  // Lê o número de sessões a serem feitas
  int n;
  if (scanf("%d", &n) != 1) {
    falha_processamento_arquivo(&f_bin);
    return;
  }

  // Itera sobre as sessões de deleção
  for (int i = 0; i < n; i++) {
    // Struct registro que serve como comparação para filtrar
    // os registros do arquivo .bin
    REG filter;

    // Array auxiliar para informar quais campos devem ser pesquisados e
    // comparados com o filtro
    bool search[PUBLIC_FIELDS];

    // Preenche a struct filter e o array search com os valores do filtro de
    // pesquisa
    filter_build(&filter, search);

    delete_loop(f_bin, &cabecalho, search, &filter);

    // Atualiza o número de estações e pares de estações no registro de
    // cabeçalho
    atualizar_estacoes(f_bin);

    // Atualiza e escreve o cabeçalho
    cabecalho.status = '1';
    escrever_cab_bin(f_bin, &cabecalho);

    // Fecha o arquivo binário e o define como NULL para evitar acessos
    // indevidos
    fclose(f_bin);
    f_bin = NULL;
  }

  BinarioNaTela(bin_name);
}
