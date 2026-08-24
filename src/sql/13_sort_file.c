#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/IO.h"
#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include "../../include/sql_functions.h"

// Função auxiliar para fechamento de múltiplos arquivos e exibição de erro.
void file_processing_failure_sort(FILE **f_in, FILE **f_out,
                                  DataRecord **array) {
  if (f_in != NULL && *f_in != NULL) {
    fclose(*f_in);
    *f_in = NULL;
  }
  if (f_out != NULL && *f_out != NULL) {
    fclose(*f_out);
    *f_out = NULL;
  }
  if (array != NULL && *array != NULL) {
    free(*array);
    *array = NULL;
  }

  printf("Falha no processamento do arquivo.\n");
}

// Função de comparação para o qsort a partir do campo codEstacao
// Faz uma ordenação crescente
int cmp_codEstacao(const void *a, const void *b) {
  const DataRecord *r1 = (const DataRecord *)a;
  const DataRecord *r2 = (const DataRecord *)b;

  return r1->codEstacao - r2->codEstacao;
}

// Função de comparação para o qsort a partir do campo codProxEstacao
// Faz uma ordenação crescente
// Valores nulos (-1) são considerados maiores que qualquer valor válido para
// ficarem no final
int cmp_codProxEstacao(const void *a, const void *b) {
  const DataRecord *r1 = (const DataRecord *)a;
  const DataRecord *r2 = (const DataRecord *)b;

  if (r1->codProxEstacao == -1 && r2->codProxEstacao != -1)
    return 1;
  if (r2->codProxEstacao == -1 && r1->codProxEstacao != -1)
    return -1;

  return r1->codProxEstacao - r2->codProxEstacao;
}

// Ordenação de um arquivo de dados na memória principal
void sort_file() {
  FILE *f_in = NULL;
  FILE *f_out = NULL;
  DataRecord *registros = NULL;

  char bin_name_in[50], campo[50], bin_name_out[50];

  // Lê o arquivo de entrada, o campo pelo qual será ordenado e o nome do
  // arquivo de saída
  if (scanf("%s %s %s", bin_name_in, campo, bin_name_out) != 3) {
    file_processing_failure_sort(&f_in, &f_out, &registros);
    return;
  }

  // Abre o arquivo de entrada
  f_in = open_binary_file(bin_name_in, "rb");
  if (f_in == NULL) {
    file_processing_failure_sort(&f_in, &f_out, &registros);
    return;
  }

  DataHeader header_in;
  if (!data_header_read(f_in, &header_in)) {
    file_processing_failure_sort(&f_in, &f_out, &registros);
    return;
  }

  // Aloca dinamicamente um vetor de registros
  int total_records = header_in.proxRRN;
  registros = (DataRecord *)malloc(total_records * sizeof(DataRecord));
  if (registros == NULL) {
    file_processing_failure_sort(&f_in, &f_out, &registros);
    return;
  }

  int qtd_validos = 0;

  // Carrega todos os registros válidos para a memória RAM
  for (int RRN = 0; RRN < total_records; RRN++) {

    // Lê o registro para a struct
    DataRecord current_record;
    if (!data_record_read(f_in, &current_record)) {
      file_processing_failure_sort(&f_in, &f_out, &registros);
      return;
    }

    if (current_record.removido == '1') {
      continue;
    }

    // Coloca o registro no array e incrementa a quantidade de registros válidos
    registros[qtd_validos] = current_record;
    qtd_validos++;
  }

  // Fecha o arquivo de entrada e "apaga" o endereço antigo do ponteiro para não
  // tentar acessar o arquivo já fechado
  fclose(f_in);
  f_in = NULL;

  // Ordena os registros utilizando qsort da stdlib com a função comparadora
  // adequada
  if (strcmp(campo, "codEstacao") == 0) {
    qsort(registros, qtd_validos, sizeof(DataRecord), cmp_codEstacao);
  } else if (strcmp(campo, "codProxEstacao") == 0) {
    qsort(registros, qtd_validos, sizeof(DataRecord), cmp_codProxEstacao);
  } else {
    // Caso um campo de ordenação inválido seja passado
    file_processing_failure_sort(&f_in, &f_out, &registros);
    return;
  }

  // Cria o arquivo de saída
  f_out = open_binary_file(bin_name_out, "wb");
  if (f_out == NULL) {
    file_processing_failure_sort(&f_in, &f_out, &registros);
    return;
  }

  // Cria o novo cabeçalho a partir do antigo mas "resetando" a remoção lógica
  DataHeader header_out;
  header_out.status = '0';
  header_out.topo = -1;
  header_out.proxRRN = qtd_validos;
  header_out.nroEstacoes = header_in.nroEstacoes;
  header_out.nroParesEstacoes = header_in.nroParesEstacoes;

  // Escreve o novo cabeçalho no arquivo
  if (!data_header_write(f_out, &header_out)) {
    file_processing_failure_sort(&f_in, &f_out, &registros);
    return;
  }

  // Grava cada um dos registros ordenados sequencialmente
  for (int i = 0; i < qtd_validos; i++) {

    if (!data_record_write(f_out, &registros[i])) {
      file_processing_failure_sort(&f_in, &f_out, &registros);
      return;
    }
  }

  // Atualiza o status do arquivo final para consistente
  header_out.status = '1';
  if (!data_header_write(f_out, &header_out)) {
    file_processing_failure_sort(&f_in, &f_out, &registros);
    return;
  }

  // Salva e fecha o arquivo
  fclose(f_out);
  f_out = NULL;

  // Libera a memória da lista de registros
  free(registros);

  BinarioNaTela(bin_name_out);
}
