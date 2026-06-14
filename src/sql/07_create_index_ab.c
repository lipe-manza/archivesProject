#include "../../include/IO.h"
#include "../../include/btree.h"
#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include <stdio.h>
#include <stdlib.h>

#define DATA_HEADER_SIZE 17
#define DATA_RECORD_SIZE 80

/**
 * @brief Função auxiliar para limpar memória e fechar arquivos em caso de erro,
 * imprimindo a mensagem padronizada exigida pela especificação.
 */
static void falha_processamento_arquivo(FILE **f1, FILE **f2, DataHeader **dh,
                                        DataRecord **dr, BTreeHeader **bth) {
  if (f1 != NULL && *f1 != NULL) {
    fclose(*f1);
    *f1 = NULL;
  }
  if (f2 != NULL && *f2 != NULL) {
    fclose(*f2);
    *f2 = NULL;
  }
  if (dh != NULL)
    data_header_destroy(dh);
  if (dr != NULL)
    data_record_destroy(dr);
  if (bth != NULL)
    btree_header_destroy(bth);

  printf("Falha no processamento do arquivo.\n");
}

/**
 * @brief Funcionalidade [7]: Cria um arquivo de índice Árvore-B a partir de
 * um arquivo de dados existente.
 */
void create_index_ab() {
  char nome_entrada[50];
  char nome_arvore_b[50];

  if (scanf("%s %s", nome_entrada, nome_arvore_b) != 2)
    return;

  FILE *f_entrada = fopen(nome_entrada, "rb");
  if (f_entrada == NULL) {
    falha_processamento_arquivo(NULL, NULL, NULL, NULL, NULL);
    return;
  }

  // O arquivo de índice precisa ser 'wb+' porque a inserção na Árvore-B
  // intercala leituras (para buscar a folha) e escritas (para salvar nós)
  FILE *f_arvore_b = fopen(nome_arvore_b, "wb+");
  if (f_arvore_b == NULL) {
    falha_processamento_arquivo(&f_entrada, NULL, NULL, NULL, NULL);
    return;
  }

  // Inicialização dos TADs
  DataHeader *cab_entrada = data_header_create();
  DataRecord *registro = data_record_create();
  BTreeHeader *headerBt = btree_header_create();

  if (cab_entrada == NULL || registro == NULL || headerBt == NULL) {
    falha_processamento_arquivo(&f_entrada, &f_arvore_b, &cab_entrada,
                                &registro, &headerBt);
    return;
  }

  // Leitura do cabeçalho do arquivo de dados
  if (!data_header_read(f_entrada, cab_entrada)) {
    falha_processamento_arquivo(&f_entrada, &f_arvore_b, &cab_entrada,
                                &registro, &headerBt);
    return;
  }

  // O status padrão do construtor já é '0' (inconsistente)
  if (!btree_header_write(f_arvore_b, headerBt)) {
    falha_processamento_arquivo(&f_entrada, &f_arvore_b, &cab_entrada,
                                &registro, &headerBt);
    return;
  }

  int prox_rrn_dados = data_header_get_proxRRN(cab_entrada);

  // Itera sobre todos os registros do arquivo de dados
  for (int RRN = 0; RRN < prox_rrn_dados; RRN++) {

    if (!data_record_read(f_entrada, registro)) {
      falha_processamento_arquivo(&f_entrada, &f_arvore_b, &cab_entrada,
                                  &registro, &headerBt);
      return;
    }

    // Registros logicamente removidos não devem ser indexados na Árvore-B
    if (data_record_get_removido(registro) == '0') {
      BTreeKey key;
      key.C = data_record_get_codEstacao(registro);

      // O byteOffset = Tamanho do Cabeçalho + (RRN * Tamanho do Registro)
      key.Pr = DATA_HEADER_SIZE + (RRN * DATA_RECORD_SIZE);

      // Insere na Árvore-B
      if (!btree_insert_key(f_arvore_b, headerBt, key)) {
        falha_processamento_arquivo(&f_entrada, &f_arvore_b, &cab_entrada,
                                    &registro, &headerBt);
        return;
      }
    }
  }

  // Atualiza o status para consistente ('1') e salva o cabeçalho final
  btree_header_set_status(headerBt, '1');
  if (!btree_header_write(f_arvore_b, headerBt)) {
    falha_processamento_arquivo(&f_entrada, &f_arvore_b, &cab_entrada,
                                &registro, &headerBt);
    return;
  }

  // Limpeza de memória (Evitando Memory Leaks)
  data_header_destroy(&cab_entrada);
  data_record_destroy(&registro);
  btree_header_destroy(&headerBt);

  fclose(f_entrada);
  fclose(f_arvore_b);

  // Validação final exigida pela especificação
  BinarioNaTela(nome_arvore_b);
}
