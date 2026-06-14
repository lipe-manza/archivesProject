#include "../../include/IO.h"
#include "../../include/btree.h"
#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include "../../include/sql_functions.h"
#include <stdio.h>
#include <stdlib.h>

#define DATA_HEADER_SIZE 17
#define DATA_RECORD_SIZE 80

/**
 * @brief Função auxiliar para fechar arquivos e evitar vazamentos de memória
 * (Memory Leaks).
 */
static void cleanup_resources(FILE **f_data, FILE **f_btree, DataHeader **dh,
                              BTreeHeader **bth, DataRecord **reg) {
  if (f_data && *f_data) {
    fclose(*f_data);
    *f_data = NULL;
  }
  if (f_btree && *f_btree) {
    fclose(*f_btree);
    *f_btree = NULL;
  }

  if (dh)
    data_header_destroy(dh);
  if (bth)
    btree_header_destroy(bth);
  if (reg)
    data_record_destroy(reg);
}

/**
 * @brief Funcionalidade [9]: Insere novos registros no arquivo de dados
 * reaproveitando espaços removidos e indexa a nova inserção na Árvore-B em
 * tempo real.
 */
void insert_into_ab() {
  char input_filename[50];
  char btree_filename[50];
  int num_insertions;

  // Lê os parâmetros iniciais da Funcionalidade [9]
  if (scanf("%s %s %d", input_filename, btree_filename, &num_insertions) != 3) {
    printf("Falha no processamento do arquivo.\n");
    return;
  }

  // Abre ambos os arquivos em modo de atualização (leitura/escrita binária)
  FILE *f_data = fopen(input_filename, "rb+");
  if (f_data == NULL) {
    printf("Falha no processamento do arquivo.\n");
    return;
  }

  FILE *f_btree = fopen(btree_filename, "rb+");
  if (f_btree == NULL) {
    printf("Falha no processamento do arquivo.\n");
    cleanup_resources(&f_data, NULL, NULL, NULL, NULL);
    return;
  }

  // Instancia os TADs
  DataHeader *data_header = data_header_create();
  BTreeHeader *btree_header = btree_header_create();
  DataRecord *new_record = data_record_create();

  // Valida as leituras dos cabeçalhos
  if (!data_header_read(f_data, data_header) ||
      !btree_header_read(f_btree, btree_header)) {
    printf("Falha no processamento do arquivo.\n");
    cleanup_resources(&f_data, &f_btree, &data_header, &btree_header,
                      &new_record);
    return;
  }

  // Checagem de consistência prévia
  if (data_header_get_status(data_header) == '0' ||
      btree_header_get_status(btree_header) == '0') {
    printf("Falha no processamento do arquivo.\n");
    cleanup_resources(&f_data, &f_btree, &data_header, &btree_header,
                      &new_record);
    return;
  }

  // Trava os arquivos definindo como inconsistentes durante o processamento
  // (Crash Recovery)
  data_header_set_status(data_header, '0');
  btree_header_set_status(btree_header, '0');
  data_header_write(f_data, data_header);
  btree_header_write(f_btree, btree_header);

  // Processa o lote de inserções
  for (int i = 0; i < num_insertions; i++) {
    // Função da IO.h que gerencia a formatação NULO e ScanQuoteString
    read_data_record_from_stdin(new_record);

    int top_stack = data_header_get_topo(data_header);
    int next_rrn = data_header_get_proxRRN(data_header);
    int target_rrn = -1;

    // Abordagem Dinâmica de Reaproveitamento de Espaços
    if (top_stack != -1) {
      target_rrn = top_stack;

      // Vai até o registro removido para descobrir o próximo da Pilha
      // (Encadeamento)
      long offset = DATA_HEADER_SIZE + (long)(target_rrn * DATA_RECORD_SIZE);
      fseek(f_data, offset, SEEK_SET);

      DataRecord *removed_record = data_record_create();
      data_record_read(f_data, removed_record);

      // Atualiza o topo do cabeçalho com o RRN encadeado
      int next_in_stack = data_record_get_proximo(removed_record);
      data_header_set_topo(data_header, next_in_stack);

      data_record_destroy(&removed_record);
    } else {
      // Se a pilha estiver vazia, insere no final do arquivo
      target_rrn = next_rrn;
      data_header_set_proxRRN(data_header, next_rrn + 1);
    }

    // Atualiza as estatísticas do arquivo de dados
    data_header_set_nroEstacoes(data_header,
                                data_header_get_nroEstacoes(data_header) + 1);
    if (data_record_get_codProxEstacao(new_record) != -1) {
      data_header_set_nroParesEstacoes(
          data_header, data_header_get_nroParesEstacoes(data_header) + 1);
    }

    // Escreve fisicamente o registro de dados (Lida com o preenchimento de lixo
    // '$')
    long byte_offset = DATA_HEADER_SIZE + (long)(target_rrn * DATA_RECORD_SIZE);
    fseek(f_data, byte_offset, SEEK_SET);
    data_record_write(f_data, new_record);

    // Prepara o DTO da Chave e insere na Árvore-B
    BTreeKey key;
    key.C = data_record_get_codEstacao(new_record);
    key.Pr = byte_offset;

    btree_insert_key(f_btree, btree_header, key);
  }

  // Libera a trava (Consistência reestabelecida)
  data_header_set_status(data_header, '1');
  btree_header_set_status(btree_header, '1');

  // Persiste as metadados finais (Nro Nos, Nro Chaves, Prox RRN, etc.)
  data_header_write(f_data, data_header);
  btree_header_write(f_btree, btree_header);

  // Destrói TADs e fecha arquivos
  cleanup_resources(&f_data, &f_btree, &data_header, &btree_header,
                    &new_record);

  // Chamadas obrigatórias para o avaliador automático do run.codes
  BinarioNaTela(input_filename);
  BinarioNaTela(btree_filename);
}
