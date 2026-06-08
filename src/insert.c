#include <stdbool.h>
#include <stdio.h>

#include "../headers/IO.h"
#include "../headers/registro.h"

void insert_into() {
  // Váriavel auxiliar para ler o nome dor arquivo
  char bin_name[50];
  // Lê o nome do arquivo binário
  if (scanf("%s", bin_name) != 1) {
    printf("Falha na leitura do nome do arquivo.\n");
    return;
  }

  // Abre o arquivo .bin para leitura e escrita e verifica se a abertura
  // foi bem sucedida conferindo o status do arquivo
  FILE *f_bin = open_bin(bin_name, "rb+");
  if (f_bin == NULL)
    return;

  // Define o arquivo binário como inconsistente no registro de cabeçalho
  // durante a escrita
  char status = '0';
  fwrite(&status, sizeof(char), 1, f_bin);

  // Vai para o campo proxRRN do registro de cabeçalho para ler quantos
  // registros existem
  int proxRRN = 0;
  fseek(f_bin, POS_PROX_RRN, SEEK_SET);
  if (fread(&proxRRN, sizeof(int), 1, f_bin) != 1) {
    printf("Falha no processamento do arquivo.\n");
    fclose(f_bin);
    return;
  }

  // Lê o número de inserções a serem feitas
  int n;
  if (scanf("%d", &n) != 1) {
    printf("Falha no processamento do arquivo.\n");
    fclose(f_bin);
    return;
  }

  // Loop para ler os registros a serem inseridos e processar cada um
  for (int i = 0; i < n; i++) {
    // Struct registro auxiliar para ler o registro do terminal
    REG registro;

    // Lê os valores do novo registro a ser inserido
    read_new_registro_from_terminal(&registro);

    // Inicializa os campos removido e próximo
    registro.removido = '0';
    registro.proximo = -1;

    // Lê o campo topo do registro de cabeçalho
    int topo = -1;
    fseek(f_bin, 1, SEEK_SET);
    if (fread(&topo, sizeof(int), 1, f_bin) != 1) {
      printf("Falha no processamento do arquivo.\n");
      fclose(f_bin);
      return;
    }

    // Se a pilha de removidos estiver vazia, insere o novo registro no
    // final do arquivo
    if (topo == -1) {
      // Vai para o byteoffset do registro de RRN == proxRRN e
      // escreve o novo registro no arquivo
      fseek(f_bin, proxRRN * TAM_REGISTRO + TAM_CABECALHO, SEEK_SET);
      write_in_bin(f_bin, &registro);

      // Atualiza o próximo RRN
      proxRRN++;
      fseek(f_bin, 5, SEEK_SET);
      fwrite(&proxRRN, sizeof(int), 1, f_bin);
    }
    // Se a pilha de removidos não estiver vazia, insere no byteoffset do
    // RRN == topo
    else {
      int byteoffset_new_registro = topo * TAM_REGISTRO + TAM_CABECALHO;

      // Lê o novo topo
      fseek(f_bin, byteoffset_new_registro + 1, SEEK_SET);
      if (fread(&topo, sizeof(int), 1, f_bin) != 1) {
        printf("Falha na atualização do topo.\n");
        fclose(f_bin);
        return;
      }

      // Atualiza o topo no registro de cabeçalho
      fseek(f_bin, 1, SEEK_SET);
      fwrite(&topo, sizeof(int), 1, f_bin);

      // Vai para o local do novo registro e escreve ele no .bin
      fseek(f_bin, byteoffset_new_registro, SEEK_SET);
      write_in_bin(f_bin, &registro);
    }
  }

  // Atualiza o número de estações e pares de estações no registro de
  // cabeçalho
  atualizar_estacoes(f_bin);

  // Atualiza o status do arquivo no registro de cabeçalho
  status = '1';
  fseek(f_bin, 0, SEEK_SET);
  fwrite(&status, sizeof(char), 1, f_bin);

  // Fecha o arquivo .bin
  fclose(f_bin);
  f_bin = NULL;

  BinarioNaTela(bin_name);
}
