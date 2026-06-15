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
void file_processing_failure_insert_bt(FILE **f_data, FILE **f_btree) {
  if (f_data && *f_data) {
    fclose(*f_data);
    *f_data = NULL;
  }
  if (f_btree && *f_btree) {
    fclose(*f_btree);
    *f_btree = NULL;
  }

  printf("Falha no processamento do arquivo.\n");
}

// Insere novos registros no arquivo de dados
// reaproveitando espaços removidos e indexa a nova inserção na Árvore-B
void insert_into_ab() {
  char input_filename[50];
  char btree_filename[50];
  int num_insertions;

  // Lê os parâmetros iniciais da
  if (scanf("%s %s %d", input_filename, btree_filename, &num_insertions) != 3) {
    printf("Falha no processamento do arquivo.\n");
    return;
  }

  // Abre ambos os arquivos em modo de atualização (leitura/escrita binária),
  // conferindo se estao consistente e setando como status inconsistentes
  FILE *f_data = open_binary_file(input_filename, "rb+");
  if (f_data == NULL) {
    file_processing_failure_insert_bt(NULL, NULL);
    return;
  }
  FILE *f_btree = open_binary_file(btree_filename, "rb+");
  if (f_btree == NULL) {
    file_processing_failure_insert_bt(&f_data, NULL);
    return;
  }

  // Instancia as structs na stack e zera a memória
  DataHeader data_header = {0};
  BTreeHeader btree_header = {0};
  DataRecord new_record = {0};

  // Valida as leituras dos cabeçalhos
  if (!data_header_read(f_data, &data_header) ||
      !btree_header_read(f_btree, &btree_header)) {
    file_processing_failure_insert_bt(&f_data, &f_btree);
    return;
  }

  // Trava os arquivos definindo como inconsistentes durante o processamento
  data_header.status = '0';
  btree_header.status = '0';
  data_header_write(f_data, &data_header);
  btree_header_write(f_btree, &btree_header);

  // Processa o lote de inserções
  for (int i = 0; i < num_insertions; i++) {
    // Lê o pedido de inserção atual e grava no new_record
    read_data_record_from_stdin(&new_record);
    new_record.removido = '0';
    new_record.proximo = -1;

    int target_key = new_record.codEstacao;
    if (btree_search_key(f_btree, &btree_header, target_key) !=
        BTREE_NOT_FOUND) {
      continue;
    }
    int top_stack = data_header.topo;
    int next_rrn = data_header.proxRRN;
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
      data_header.topo = next_in_stack;
    } else {
      // Se a pilha estiver vazia, insere no final do arquivo
      target_rrn = next_rrn;
      // Atualiza o próximo rrn disponível
      data_header.proxRRN = next_rrn + 1;
    }

    // Escreve fisicamente o registro de dados
    long byte_offset = DATA_HEADER_SIZE + (long)(target_rrn * DATA_RECORD_SIZE);
    fseek(f_data, byte_offset, SEEK_SET);
    data_record_write(f_data, &new_record);

    // Prepara a chave a ser inserida
    BTreeKey key;
    key.C = new_record.codEstacao;
    key.Pr = byte_offset;

    // Insere a chave na B-Tree
    btree_insert_key(f_btree, &btree_header, key);
  }

  // Atualiza os dados de cabecalhos
  data_header.status = '1';
  btree_header.status = '1';

  update_statistics(f_data, &data_header);
  data_header_write(f_data, &data_header);
  btree_header_write(f_btree, &btree_header);

  // Fecha arquivos
  fclose(f_data);
  f_data = NULL;
  fclose(f_btree);
  f_btree = NULL;

  // Chamadas obrigatórias para o avaliador automático do run.codes
  BinarioNaTela(input_filename);
  BinarioNaTela(btree_filename);
}
