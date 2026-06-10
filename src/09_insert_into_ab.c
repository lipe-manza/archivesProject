#include <stdbool.h>
#include <stdio.h>

#include "../headers/IO.h"
#include "../headers/registro.h"
#include "../headers/sql_functions.h"

// Função auxiliar para fechar os arquivos
void close_files(FILE *f_entrada, FILE *f_arvore_b) {
  if (f_entrada)
    fclose(f_entrada);
  if (f_arvore_b)
    fclose(f_arvore_b);
}

void insert_into() {
  // Variável auxiliar para ler o nome do arquivo
  char bin_name[50];
  // Lê o nome do arquivo binário
  if (scanf("%s", bin_name) != 1) {
    printf("Falha na leitura do nome do arquivo.\n");
    return;
  }

  // Abre o arquivo binário de entrada para leitura e escrita e verifica se a
  // abertura foi bem sucedida conferindo o status do arquivo
  FILE *f_entrada = open_bin(bin_name, "rb+");
  if (f_entrada == NULL)
    return;

  // Abre o arquivo binário da árvore B para leitura e escrita e verifica se a
  // abertura foi bem sucedida conferindo o status do arquivo
  FILE *f_arvore_b = open_bin(bin_name, "rb+");
  if (f_arvore_b == NULL) {
    fclose(f_entrada);
    return;
  }

  // Define o arquivo binário como inconsistente no registro de cabeçalho
  // durante a escrita
  char status = '0';
  fwrite(&status, sizeof(char), 1, f_entrada);

  // Vai para o campo proxRRN do registro de cabeçalho para ler quantos
  // registros existem
  int proxRRN = 0;
  fseek(f_entrada, POS_PROX_RRN, SEEK_SET);
  if (fread(&proxRRN, sizeof(int), 1, f_entrada) != 1) {
    printf("Falha no processamento do arquivo.\n");
    close_files(f_entrada, f_arvore_b);
    return;
  }

  // Lê o número de inserções a serem feitas
  int n;
  if (scanf("%d", &n) != 1) {
    printf("Falha no processamento do arquivo.\n");
    close_files(f_entrada, f_arvore_b);
    return;
  }

  // Loop para ler os registros a serem inseridos e processar cada um
  for (int i = 0; i < n; i++) {
    // Struct registro auxiliar para ler o registro do terminal
    REG registro;

    read_to_and_insert(&registro, f_entrada, proxRRN);
    // INSERIR NA ÁRVORE B
  }

  // Atualiza o número de estações e pares de estações no registro de
  // cabeçalho
  atualizar_estacoes(f_entrada);

  // Atualiza o status do arquivo no registro de cabeçalho
  status = '1';
  fseek(f_entrada, 0, SEEK_SET);
  fwrite(&status, sizeof(char), 1, f_entrada);

  // Fecha os arquivos binários
  close_files(f_entrada, f_arvore_b);
  f_entrada = NULL;
  f_arvore_b = NULL;

  BinarioNaTela(bin_name);
}
