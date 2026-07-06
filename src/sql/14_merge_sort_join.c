#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/IO.h"
#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include "../../include/sql_functions.h"

// Função auxiliar de limpeza para a funcionalidade de Merge Sort Join.
void file_processing_failure_merge(FILE **f_bin1, FILE **f_bin2,
                                   DataRecord **arr1, DataRecord **arr2) {
  if (f_bin1 != NULL && *f_bin1 != NULL) {
    fclose(*f_bin1);
    *f_bin1 = NULL;
  }
  if (f_bin2 != NULL && *f_bin2 != NULL) {
    fclose(*f_bin2);
    *f_bin2 = NULL;
  }
  if (arr1 != NULL && *arr1 != NULL) {
    free(*arr1);
    *arr1 = NULL;
  }
  if (arr2 != NULL && *arr2 != NULL) {
    free(*arr2);
    *arr2 = NULL;
  }

  printf("Falha no processamento do arquivo.\n");
}

// Comparador para o qsort no arquivo 1 (ordenado pelo campo codProxEstacao)
static int cmp_codProxEstacao_merge(const void *a, const void *b) {
  const DataRecord *r1 = (const DataRecord *)a;
  const DataRecord *r2 = (const DataRecord *)b;

  // Valores nulos vão para o final
  if (r1->codProxEstacao == -1 && r2->codProxEstacao != -1)
    return 1;
  if (r2->codProxEstacao == -1 && r1->codProxEstacao != -1)
    return -1;

  return r1->codProxEstacao - r2->codProxEstacao;
}

// Comparador para o qsort no arquivo 2 (ordenado pelo campo codEstacao)
static int cmp_codEstacao_merge(const void *a, const void *b) {
  const DataRecord *r1 = (const DataRecord *)a;
  const DataRecord *r2 = (const DataRecord *)b;

  if (r1->codEstacao == -1 && r2->codEstacao != -1)
    return 1;
  if (r2->codEstacao == -1 && r1->codEstacao != -1)
    return -1;

  return r1->codEstacao - r2->codEstacao;
}

// Funcionalidade 14: Ordenação-Intercalação (Merge Sort Join)
// Realiza a junção na memória RAM após ordenação baseada nos atributos da
// condição de junção.
void merge_sort_join() {
  FILE *f_bin1 = NULL;
  FILE *f_bin2 = NULL;
  DataRecord *registros1 = NULL;
  DataRecord *registros2 = NULL;

  char bin_name1[50], field1[50];
  char bin_name2[50], field2[50];

  // Leitura dos nomes e dos campos
  if (scanf("%s %s", bin_name1, field1) != 2) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &registros1, &registros2);
    return;
  }
  if (scanf("%s %s", bin_name2, field2) != 2) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &registros1, &registros2);
    return;
  }

  // Abertura e validação do primeiro arquivo
  f_bin1 = open_binary_file(bin_name1, "rb");
  if (f_bin1 == NULL) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &registros1, &registros2);
    return;
  }
  DataHeader header1;
  if (!data_header_read(f_bin1, &header1)) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &registros1, &registros2);
    return;
  }

  // Abertura e validação do segundo arquivo
  f_bin2 = open_binary_file(bin_name2, "rb");
  if (f_bin2 == NULL) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &registros1, &registros2);
    return;
  }
  DataHeader header2;
  if (!data_header_read(f_bin2, &header2)) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &registros1, &registros2);
    return;
  }

  // Aloca a memória exata para a carga completa dos registros
  registros1 = (DataRecord *)malloc(header1.proxRRN * sizeof(DataRecord));
  registros2 = (DataRecord *)malloc(header2.proxRRN * sizeof(DataRecord));

  if (registros1 == NULL || registros2 == NULL) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &registros1, &registros2);
    return;
  }

  int count1 = 0;
  int count2 = 0;

  // Carrega e filtra o arquivo 1
  fseek(f_bin1, HEADER_SIZE, SEEK_SET);
  for (int rrn = 0; rrn < header1.proxRRN; rrn++) {
    DataRecord current_record;
    if (!data_record_read(f_bin1, &current_record)) {
      file_processing_failure_merge(&f_bin1, &f_bin2, &registros1, &registros2);
      return;
    }
    if (current_record.removido != '1') {
      registros1[count1++] = current_record;
    }
  }

  // Carrega e filtra o arquivo 2
  fseek(f_bin2, HEADER_SIZE, SEEK_SET);
  for (int rrn = 0; rrn < header2.proxRRN; rrn++) {
    DataRecord current_record;
    if (!data_record_read(f_bin2, &current_record)) {
      file_processing_failure_merge(&f_bin1, &f_bin2, &registros1, &registros2);
      return;
    }
    if (current_record.removido != '1') {
      registros2[count2++] = current_record;
    }
  }

  // Ordena os arrays baseado na especificação (codProxEstacao para o arq1,
  // codEstacao para o arq2)
  qsort(registros1, count1, sizeof(DataRecord), cmp_codProxEstacao_merge);
  qsort(registros2, count2, sizeof(DataRecord), cmp_codEstacao_merge);

  // Fecha os arquivos pois não acessaremos o disco durante o merge
  fclose(f_bin1);
  f_bin1 = NULL;
  fclose(f_bin2);
  f_bin2 = NULL;

  int i = 0, j = 0;
  bool found = false;

  // Intercala (Merge) simultâneo buscando a condição: estacao1.codProxEstacao
  // == estacao2.codEstacao
  while (i < count1 && j < count2) {
    // Para no primeiro valor nulo detectado, já que as funções os jogam para o
    // final
    if (registros1[i].codProxEstacao == -1 || registros2[j].codEstacao == -1) {
      break;
    }

    if (registros1[i].codProxEstacao < registros2[j].codEstacao) {
      i++;
    } else if (registros1[i].codProxEstacao > registros2[j].codEstacao) {
      j++;
    } else {
      // Cruzamento encontrado
      found = true;

      // Impressão padronizada, ignorando dados ausentes
      if (registros1[i].codEstacao == -1)
        printf("NULO ");
      else
        printf("%d ", registros1[i].codEstacao);

      if (strlen(registros1[i].nomeEstacao) == 0)
        printf("NULO ");
      else
        printf("%s ", registros1[i].nomeEstacao);

      if (strlen(registros1[i].nomeLinha) == 0)
        printf("NULO ");
      else
        printf("%s ", registros1[i].nomeLinha);

      if (registros1[i].codProxEstacao == -1)
        printf("NULO ");
      else
        printf("%d ", registros1[i].codProxEstacao);

      if (strlen(registros2[j].nomeEstacao) == 0)
        printf("NULO\n");
      else
        printf("%s\n", registros2[j].nomeEstacao);

      // Avançamos somente o 'i'. Em relacionamentos N-para-1 onde codEstacao é
      // PK, Múltiplos registros de estacao1 podem apontar para a mesma
      // estacao2.
      i++;
    }
  }

  if (!found) {
    printf("Registro inexistente.\n");
  }

  free(registros1);
  free(registros2);
}
