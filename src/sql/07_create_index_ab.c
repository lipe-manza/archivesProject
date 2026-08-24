#include "../../include/IO.h"
#include "../../include/btree.h"
#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include <stdio.h>
#include <stdlib.h>

#define DATA_HEADER_SIZE 17
#define DATA_RECORD_SIZE 80

// Função auxiliar para limpar memória e fechar arquivos em caso de erro,
static void file_processing_failure_create_index(FILE **f1, FILE **f2) {
  if (f1 != NULL && *f1 != NULL) {
    fclose(*f1);
    *f1 = NULL;
  }
  if (f2 != NULL && *f2 != NULL) {
    fclose(*f2);
    *f2 = NULL;
  }

  printf("Falha no processamento do arquivo.\n");
}

// Cria um arquivo de índice Árvore-B a partir de
// um arquivo de dados existente.
void create_index() {
  char nome_entrada[50];
  char nome_arvore_b[50];

  if (scanf("%s %s", nome_entrada, nome_arvore_b) != 2)
    return;

  // Abre para leitura e verifica se está consistente
  FILE *f_entrada = open_binary_file(nome_entrada, "rb");
  if (f_entrada == NULL) {
    file_processing_failure_create_index(NULL, NULL);
    return;
  }

  // O arquivo de índice precisa ser 'wb+' porque a inserção na Árvore-B
  // precisa ler(ver se a key já existe) e escrever(inserir) no disco
  // Marca o status como inconstistente
  FILE *f_arvore_b = open_binary_file(nome_arvore_b, "wb+");
  if (f_arvore_b == NULL) {
    file_processing_failure_create_index(&f_entrada, NULL);
    return;
  }

  // Inicialização das structs na stack
  DataHeader cab_entrada;
  DataRecord registro;
  BTreeHeader headerBt = {'0', -1, -1, 0, 0};

  // Leitura do cabeçalho do arquivo de dados
  if (!data_header_read(f_entrada, &cab_entrada)) {
    file_processing_failure_create_index(&f_entrada, &f_arvore_b);
    return;
  }

  // O status padrão do construtor já é '0' (inconsistente)
  if (!btree_header_write(f_arvore_b, &headerBt)) {
    file_processing_failure_create_index(&f_entrada, &f_arvore_b);
    return;
  }

  int prox_rrn_dados = cab_entrada.proxRRN;

  // Itera sobre todos os registros do arquivo de dados
  for (int RRN = 0; RRN < prox_rrn_dados; RRN++) {

    // Tenta ler o registro atual
    if (!data_record_read(f_entrada, &registro)) {
      file_processing_failure_create_index(&f_entrada, &f_arvore_b);
      return;
    }

    // Se for lógicamente removido não insere na B-Tree
    if (registro.removido == '0') {
      BTreeKey key;
      key.C = registro.codEstacao;

      // O byteOffset = Tamanho do Cabeçalho + (RRN * Tamanho do Registro)
      key.Pr = DATA_HEADER_SIZE + (RRN * DATA_RECORD_SIZE);

      // Insere na Árvore-B
      if (!btree_insert_key(f_arvore_b, &headerBt, key)) {
        file_processing_failure_create_index(&f_entrada, &f_arvore_b);
        return;
      }
    }
  }

  // Atualiza o status para consistente ('1') e salva o cabeçalho final
  headerBt.status = '1';
  if (!btree_header_write(f_arvore_b, &headerBt)) {
    file_processing_failure_create_index(&f_entrada, &f_arvore_b);
    return;
  }

  // Fecha os arquivos
  fclose(f_entrada);
  fclose(f_arvore_b);

  BinarioNaTela(nome_arvore_b);
}
