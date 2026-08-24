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

// Realiza a junção na memória RAM após ordenação baseada nos atributos da
// condição de junção.
void merge_sort_join() {
  FILE *f_bin1 = NULL;
  FILE *f_bin2 = NULL;
  DataRecord *records1 = NULL;
  DataRecord *records2 = NULL;

  char bin_name1[50], field1[50];
  char bin_name2[50], field2[50];

  // Leitura dos nomes e dos campos
  if (scanf("%s %s", bin_name1, field1) != 2) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &records1, &records2);
    return;
  }
  if (scanf("%s %s", bin_name2, field2) != 2) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &records1, &records2);
    return;
  }

  // Abertura e validação do primeiro arquivo utilizando o open_binary_file
  f_bin1 = open_binary_file(bin_name1, "rb+");
  if (f_bin1 == NULL) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &records1, &records2);
    return;
  }
  DataHeader header1;
  if (!data_header_read(f_bin1, &header1)) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &records1, &records2);
    return;
  }
  // Atualiza o status do cabeçalho para inconsistente
  header1.status = '0';

  // Abertura e validação do segundo arquivo utilizando o open_binary_file
  f_bin2 = open_binary_file(bin_name2, "rb+");
  if (f_bin2 == NULL) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &records1, &records2);
    return;
  }
  DataHeader header2;
  if (!data_header_read(f_bin2, &header2)) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &records1, &records2);
    return;
  }
  // Atualiza o status do cabeçalho para inconsistente
  header2.status = '0';

  // Aloca a memória necessária para armazenar os dois registros na HEAP(um
  // pouco a mais, visto que não guarda registros removidos na HEAP)
  records1 = (DataRecord *)malloc(header1.proxRRN * sizeof(DataRecord));
  records2 = (DataRecord *)malloc(header2.proxRRN * sizeof(DataRecord));

  if (records1 == NULL || records2 == NULL) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &records1, &records2);
    return;
  }

  int count1 = 0;
  int count2 = 0;

  // Carrega e filtra o arquivo 1
  for (int rrn = 0; rrn < header1.proxRRN; rrn++) {
    DataRecord current_record;
    if (!data_record_read(f_bin1, &current_record)) {
      file_processing_failure_merge(&f_bin1, &f_bin2, &records1, &records2);
      return;
    }
    if (current_record.removido != '1') {
      records1[count1++] = current_record;
    }
  }

  // Carrega e filtra o arquivo 2
  for (int rrn = 0; rrn < header2.proxRRN; rrn++) {
    DataRecord current_record;
    if (!data_record_read(f_bin2, &current_record)) {
      file_processing_failure_merge(&f_bin1, &f_bin2, &records1, &records2);
      return;
    }
    if (current_record.removido != '1') {
      records2[count2++] = current_record;
    }
  }

  // Ordena os registros baseado utilizando, codProxEstacao para o arq1,
  // codEstacao para o arq2, deixando os NULOS no final
  qsort(records1, count1, sizeof(DataRecord), cmp_codProxEstacao_merge);
  qsort(records2, count2, sizeof(DataRecord), cmp_codEstacao_merge);

  // Reescreve os arquivos de dados ordenadamente

  // Atualiza o cabeçalho a partir do antigo mas "resetando" a remoção lógica
  header1.topo = -1;
  header1.proxRRN = count1;
  header1.nroEstacoes = header1.nroEstacoes;
  header1.nroParesEstacoes = header1.nroParesEstacoes;

  // Fecha o arquivo rb+ e reabre como wb para truncar (remover lixo no final)
  fclose(f_bin1);
  f_bin1 = open_binary_file(bin_name1, "wb");
  if (f_bin1 == NULL) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &records1, &records2);
    return;
  }

  // Escreve o novo cabeçalho no arquivo
  if (!data_header_write(f_bin1, &header1)) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &records1, &records2);
    return;
  }

  // Grava cada um dos registros ordenados sequencialmente
  for (int i = 0; i < count1; i++) {

    if (!data_record_write(f_bin1, &records1[i])) {
      file_processing_failure_merge(&f_bin1, &f_bin2, &records1, &records2);
      return;
    }
  }

  // Atualiza o status do arquivo final para consistente
  header1.status = '1';
  if (!data_header_write(f_bin1, &header1)) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &records1, &records2);
    return;
  }

  // Salva e fecha o arquivo 1
  fclose(f_bin1);
  f_bin1 = NULL;

  // Atualiza o cabeçalho a partir do antigo mas "resetando" a remoção lógica
  header2.topo = -1;
  header2.proxRRN = count2;
  header2.nroEstacoes = header2.nroEstacoes;
  header2.nroParesEstacoes = header2.nroParesEstacoes;

  // Fecha o arquivo rb+ e reabre como wb para truncar (remover lixo no final)
  fclose(f_bin2);
  f_bin2 = open_binary_file(bin_name2, "wb");
  if (f_bin2 == NULL) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &records1, &records2);
    return;
  }

  // Escreve o novo cabeçalho no arquivo
  if (!data_header_write(f_bin2, &header2)) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &records1, &records2);
    return;
  }

  // Grava cada um dos registros ordenados sequencialmente
  for (int i = 0; i < count2; i++) {

    if (!data_record_write(f_bin2, &records2[i])) {
      file_processing_failure_merge(&f_bin1, &f_bin2, &records1, &records2);
      return;
    }
  }

  // Atualiza o status do arquivo final para consistente
  header2.status = '1';
  if (!data_header_write(f_bin2, &header2)) {
    file_processing_failure_merge(&f_bin1, &f_bin2, &records1, &records2);
    return;
  }

  // Salva e fecha o arquivo 2
  fclose(f_bin2);
  f_bin2 = NULL;

  // Variáveis auxiliares
  int i = 0, j = 0;
  bool found = false;

  // Percorre os dois registros ordenados ao mesmo tempo procurando registros
  // que satisfaçam a condição estacao1.codProxEstacao == estacao2.codEstacao.
  while (i < count1 && j < count2) {
    // Para no primeiro valor nulo detectado, já que as funções os jogam para o
    // final
    if (records1[i].codProxEstacao == -1) {
      break;
    }

    if (records1[i].codProxEstacao < records2[j].codEstacao) {
      i++;
    } else if (records1[i].codProxEstacao > records2[j].codEstacao) {
      j++;
    } else {
      // Cruzamento encontrado
      found = true;

      // Impressão padronizada, ignorando dados ausentes
      printf("%d ", records1[i].codEstacao);

      printf("%s ", records1[i].nomeEstacao);

      if (strlen(records1[i].nomeLinha) == 0)
        printf("NULO ");
      else
        printf("%s ", records1[i].nomeLinha);

      if (records1[i].codProxEstacao == -1)
        printf("NULO ");
      else
        printf("%d ", records1[i].codProxEstacao);

      printf("%s\n", records2[j].nomeEstacao);

      // Avança apenas o 'i', pois há uma relação N para 1:
      // várias estações podem ter o mesmo codProxEstacao.
      i++;
    }
  }

  if (!found) {
    printf("Registro inexistente.\n");
  }

  // Da free nas memórias alocadas
  free(records1);
  free(records2);
}
