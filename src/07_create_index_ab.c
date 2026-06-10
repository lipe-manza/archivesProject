#include <stdbool.h>
#include <stdio.h>

#include "../headers/IO.h"
#include "../headers/registro.h"

// Função auxiliar para fechar os arquivos
void close_files(FILE *f_entrada, FILE *f_arvore_b) {
  if (f_entrada)
    fclose(f_entrada);
  if (f_arvore_b)
    fclose(f_arvore_b);
}

// Função principal para converter o arquivo .csv para .bin
void create_index_ab() {
  // Leitura dos nomes dos arquivos binários de entrada e de indexação da árvore
  // B
  char nome_entrada[50];
  char nome_arvore_b[50];

  if (scanf("%s %s", nome_entrada, nome_arvore_b) != 2)
    return;

  // Abertura do arquivo binário de entrada para leitura
  FILE *f_entrada = fopen(nome_entrada, "rb");
  if (f_entrada == NULL) {
    printf("Falha no processamento do arquivo.\n");
    return;
  }

  // Criação do arquivo da árvore B com escrita binária
  FILE *f_arvore_b = fopen(nome_arvore_b, "wb");
  if (f_arvore_b == NULL) {
    fclose(f_entrada);
    printf("Falha na criação do arquivo.\n");
    return;
  }

  // Escrita do registro de cabeçalho inicialização
  {
    // Escreve o nó raiz como -1, já que a árvore começa vazia
    int noRaiz = -1;
    fwrite(&noRaiz, sizeof(int), 1, f_arvore_b);

    // Escreve -1 como o RRN do topo da pilha de registros logicamente removidos
    // pois está vazia
    int topo = -1;
    fwrite(&topo, sizeof(int), 1, f_arvore_b);

    // Escreve o número de nós como 0 já que a árvore está vazia
    int nroNos = 0;
    fwrite(&nroNos, sizeof(int), 1, f_arvore_b);
  }

  // Pula o cabeçalho do arquivo de entrada
  fseek(f_entrada, TAM_CABECALHO, SEEK_SET);

  // Vai para o campo proxRRN do registro de cabeçalho do arquivo de entrada
  // para ler quantos registros existem
  int reg_count = 0;
  fseek(f_entrada, POS_PROX_RRN, SEEK_SET);
  if (fread(&reg_count, sizeof(int), 1, f_entrada) != 1) {
    printf("Falha no processamento do arquivo.\n");
    close_files(f_entrada, f_arvore_b);
    return;
  }

  // Struct registro auxiliar para ler os registros do arquivo de entrada
  REG registro;

  // Pula para a posição do primeiro registro
  fseek(f_entrada, TAM_CABECALHO, SEEK_SET);

  // Itera sobre os registros do arquivo de entrada e os insere na árvore B
  for (int RRN = 0; RRN < reg_count; RRN++) {
    // Lê o registro do arquivo de entrada para a struct registro
    if (!read_from_bin(f_entrada, &registro)) {
      printf("Falha na leitura do arquivo");
      close_files(f_entrada, f_arvore_b);
      return;
    };

    // O registro só é impresso se não estiver removido
    if (registro.removido == '0') {
      // INSERIR NA ARVORE B
    }
  }

  // Escrita do registro de cabeçalho

  // Aponta para o inicio do arquivo binário e escreve o status como
  // consistente pois o arquivo foi escrito com sucesso
  fseek(f_arvore_b, 0, SEEK_SET);
  int status = '1';
  fwrite(&status, sizeof(char), 1, f_arvore_b);

  // ESCREVER AS COISAS NO CABEÇALHO

  // Fecha os arquivos binários
  close_files(f_entrada, f_arvore_b);

  BinarioNaTela(nome_arvore_b);

  return;
}
