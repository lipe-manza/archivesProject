#include "../../headers/B_tree.h"
#include "../../headers/IO.h"
#include "../../headers/registro.h"

// Função auxiliar para evitar repetição quando há falha no processamento do
// arquivo
void falha_processamento_arquivo(FILE **f1, FILE **f2) {
  if (f1 != NULL && *f1 != NULL) {
    fclose(*f1);
    *f1 = NULL;
  }
  if (f2 != NULL && *f2 != NULL) {
    fclose(*f2);
    *f2 = NULL;
  }

  printf("Falha no processamento do arquivo.");
}

// Função principal para converter o arquivo .csv para .bin
void create_index_ab() {
  FILE *f_entrada = NULL;
  FILE *f_arvore_b = NULL;

  // Leitura dos nomes dos arquivos binários de entrada e de indexação da árvore
  // B
  char nome_entrada[50];
  char nome_arvore_b[50];

  if (scanf("%s %s", nome_entrada, nome_arvore_b) != 2)
    return;

  // Abertura do arquivo binário de entrada para leitura
  f_entrada = fopen(nome_entrada, "rb");
  if (f_entrada == NULL) {
    falha_processamento_arquivo(&f_entrada, &f_arvore_b);
    return;
  }

  // Criação do arquivo da árvore B com escrita binária
  f_arvore_b = fopen(nome_arvore_b, "wb");
  if (f_arvore_b == NULL) {
    falha_processamento_arquivo(&f_entrada, &f_arvore_b);
    return;
  }

  // Cria a struct do cabeçalho do arquivo de entrada
  CAB cab_entrada;
  ler_cab_bin(f_entrada, &cab_entrada);

  tornar_inconsistente(f_arvore_b);

  // Cria a struct do cabeçalho do arquivo da árvore B
  HEADER_BT headerBt;
  builder_header_B_tree(&headerBt, '0', -1, -1, 0, 0);

  write_B_tree_header_in_bin(f_arvore_b, &headerBt);

  // Struct registro auxiliar para ler os registros do arquivo de entrada
  REG registro;

  // Pula para a posição do primeiro registro
  fseek(f_entrada, TAM_CABECALHO, SEEK_SET);

  // Itera sobre os registros do arquivo de entrada e os insere na árvore B
  for (int RRN = 0; RRN < cab_entrada.proxRRN; RRN++) {
    // Lê o registro do arquivo de entrada para a struct registro
    if (!ler_reg_bin(f_entrada, &registro)) {
      falha_processamento_arquivo(&f_entrada, &f_arvore_b);
      return;
    };

    // O registro só é impresso se não estiver removido
    if (registro.removido == '0') {

      KEY key;
      key.value = registro.codEstacao;
      key.byteOffset = REG_BYTE_OFFSET(RRN);

      // CONTINUAR AQUI
      // inserir_bt(f_bt, &cab_bt, key)
    }
  }

  // Atualiza e escreve o cabeçalho
  headerBt.status = '1';
  write_B_tree_header_in_bin(f_arvore_b, &headerBt);

  // Fecha os arquivos binários
  fclose(f_entrada);
  f_entrada = NULL;

  fclose(f_arvore_b);
  f_arvore_b = NULL;

  BinarioNaTela(nome_arvore_b);

  return;
}
