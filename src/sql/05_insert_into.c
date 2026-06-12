#include "../../headers/IO.h"
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

void read_insert_reg(FILE **f_bin, CAB *cabecalho, REG *registro) {
  if (f_bin == NULL || *f_bin == NULL || cabecalho == NULL || registro == NULL)
    return;

  // Lê os valores do novo registro a ser inserido
  read_new_registro_from_terminal(registro);

  // Inicializa os campos removido e próximo
  registro->removido = '0';
  registro->proximo = -1;

  // Se a pilha de removidos estiver vazia, insere o novo registro no
  // final do arquivo
  if (cabecalho->topo == -1) {
    // Vai para o byteoffset do registro de RRN == proxRRN e
    // escreve o novo registro no arquivo
    fseek(*f_bin, REG_BYTE_OFFSET(cabecalho->proxRRN), SEEK_SET);
    escrever_reg_bin(*f_bin, registro);

    // Atualiza o próximo RRN (apenas a variável, não no arquivo binário)
    cabecalho->proxRRN++;
  }
  // Se a pilha de removidos não estiver vazia, insere no byteoffset do
  // RRN == topo
  else {
    int novo_topo = -1;

    // Lê o novo topo
    fseek(*f_bin, REG_BYTE_OFFSET(cabecalho->topo) + POS_PROX_REG, SEEK_SET);
    if (fread(&novo_topo, sizeof(int), 1, *f_bin) != 1) {
      falha_processamento_arquivo(f_bin);
      return;
    }

    // Vai para o local do novo registro e escreve ele no .bin
    fseek(*f_bin, REG_BYTE_OFFSET(cabecalho->topo), SEEK_SET);
    escrever_reg_bin(*f_bin, registro);

    // Atualiza o topo na struct do cabeçalho
    cabecalho->topo = novo_topo;
  }
}

void insert_into() {
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

  // Lê o número de inserções a serem feitas
  int n;
  if (scanf("%d", &n) != 1) {
    falha_processamento_arquivo(&f_bin);
    return;
  }

  // Loop para ler os registros a serem inseridos e processar cada um
  for (int i = 0; i < n; i++) {
    // Struct registro auxiliar para ler o registro do terminal
    REG registro;

    read_insert_reg(&f_bin, &cabecalho, &registro);
  }

  // Atualiza o número de estações e pares de estações no registro de
  // cabeçalho
  atualizar_estacoes(f_bin);

  // Atualiza e escreve o cabeçalho
  cabecalho.status = '1';
  escrever_cab_bin(f_bin, &cabecalho);

  // Fecha o arquivo .bin
  fclose(f_bin);
  f_bin = NULL;

  BinarioNaTela(bin_name);
}
