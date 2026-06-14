#include "../../include/IO.h"
#include "../../include/btree.h"
#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include "../../include/sql_functions.h"
#include "../../include/tools.h"
#include <stdio.h>
#include <stdlib.h>

#define DATA_HEADER_SIZE 17
#define DATA_RECORD_SIZE 80

// Função auxiliar para fechar arquivos e evitar vazamentos de memória
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

// Funcionalidade [9]: Insere novos registros no arquivo de dados
// reaproveitando espaços removidos e indexa a nova inserção na Árvore-B
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
  update_statistics(f_data, data_header);
  data_header_write(f_data, data_header);
  btree_header_write(f_btree, btree_header);

  // Processa o lote de inserções
  for (int i = 0; i < num_insertions; i++) {
    // Lê o pedido de inserção atual e grava no new_record
    read_data_record_from_stdin(new_record);

    int target_key = data_record_get_codEstacao(new_record);
    if (btree_search_key(f_btree, btree_header, target_key) !=
        BTREE_NOT_FOUND) {
      continue;
    }
    int top_stack = data_header_get_topo(data_header);
    int next_rrn = data_header_get_proxRRN(data_header);
    int target_rrn = -1;

    // Abordagem Dinâmica de Reaproveitamento de Espaços
    if (top_stack != -1) {
      target_rrn = top_stack;

      // Lê diretamente o campo 'proximo' do registro removido (byte offset 1-4)
      long offset = DATA_HEADER_SIZE + (long)(target_rrn * DATA_RECORD_SIZE);
      fseek(f_data, offset + 1, SEEK_SET); // Pula o byte 'removido'

      int next_in_stack = -1;
      fread(&next_in_stack, sizeof(int), 1, f_data);

      // Atualiza o topo do cabeçalho com o RRN encadeado
      data_header_set_topo(data_header, next_in_stack);
    } else {
      // Se a pilha estiver vazia, insere no final do arquivo
      target_rrn = next_rrn;
      // Atualiza o próximo rrn disponível
      data_header_set_proxRRN(data_header, next_rrn + 1);
    }

    // Escreve fisicamente o registro de dados
    long byte_offset = DATA_HEADER_SIZE + (long)(target_rrn * DATA_RECORD_SIZE);
    fseek(f_data, byte_offset, SEEK_SET);
    data_record_write(f_data, new_record);

    // Prepara a chave a ser inserida
    BTreeKey key;
    key.C = data_record_get_codEstacao(new_record);
    key.Pr = byte_offset;

    btree_insert_key(f_btree, btree_header, key);
  }

  // Libera a trava (Consistência reestabelecida)
  data_header_set_status(data_header, '1');
  btree_header_set_status(btree_header, '1');

  // Persiste as metadados finais (Nro Nos, Nro Chaves, Prox RRN, etc.)
  update_statistics(f_data, data_header);
  data_header_write(f_data, data_header);
  btree_header_write(f_btree, btree_header);

  // Destrói TADs e fecha arquivos
  cleanup_resources(&f_data, &f_btree, &data_header, &btree_header,
                    &new_record);

  // Chamadas obrigatórias para o avaliador automático do run.codes
  BinarioNaTela(input_filename);
  BinarioNaTela(btree_filename);
}
