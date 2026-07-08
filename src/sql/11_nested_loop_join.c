#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../../include/IO.h"
#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include "../../include/sql_functions.h"

// Função auxiliar para evitar repetição de código quando há falha no
// processamento. Fecha os arquivos abertos e imprime a mensagem de erro.
void file_processing_failure_join(FILE **f_bin1, FILE **f_bin2) {
  if (f_bin1 != NULL && *f_bin1 != NULL) {
    fclose(*f_bin1);
    *f_bin1 = NULL;
  }
  if (f_bin2 != NULL && *f_bin2 != NULL) {
    fclose(*f_bin2);
    *f_bin2 = NULL;
  }

  printf("Falha no processamento do arquivo.\n");
}

// Realiza a junção de dois arquivos de dados através de dois laços aninhados
// A condição de junção é que o codProxEstacao do primeiro arquivo deve ser
// igual ao codEstacao do segundo
void nested_loop_join() {
  FILE *f_bin1 = NULL;
  FILE *f_bin2 = NULL;
  DataHeader header1, header2;
  DataRecord record1, record2;

  char bin_name1[50], field1[50];
  char bin_name2[50], field2[50];

  // Lê os nomes dos arquivos e dos campos que serão utilizados para a junção
  if (scanf("%s %s", bin_name1, field1) != 2) {
    file_processing_failure_join(&f_bin1, &f_bin2);
    return;
  }

  if (scanf("%s %s", bin_name2, field2) != 2) {
    file_processing_failure_join(&f_bin1, &f_bin2);
    return;
  }

  // Abre o primeiro arquivo binário para leitura e verifica possíveis erros
  f_bin1 = open_binary_file(bin_name1, "rb");
  if (f_bin1 == NULL) {
    file_processing_failure_join(&f_bin1, &f_bin2);
    return;
  }

  // Abre o segundo arquivo binário para leitura e verifica possíveis erros
  f_bin2 = open_binary_file(bin_name2, "rb");
  if (f_bin2 == NULL) {
    file_processing_failure_join(&f_bin1, &f_bin2);
    return;
  }

  // Lê os cabeçalhos dos arquivos
  if (!data_header_read(f_bin1, &header1)) {
    file_processing_failure_join(&f_bin1, &f_bin2);
    return;
  }

  if (!data_header_read(f_bin2, &header2)) {
    file_processing_failure_join(&f_bin1, &f_bin2);
    return;
  }

  bool found = false;

  // Guarda a quantidade de registros de cada arquivo para percorrê-los
  int total_records1 = header1.proxRRN;
  int total_records2 = header2.proxRRN;

  // Itera sobre todos os registros do primeiro arquivo
  for (int RRN1 = 0; RRN1 < total_records1; RRN1++) {

    // Lê os registros do primeiro arquivo
    if (!data_record_read(f_bin1, &record1)) {
      file_processing_failure_join(&f_bin1, &f_bin2);
      return;
    }

    // Ignora registros que foram removidos logicamente
    if (record1.removido == '1') {
      continue;
    }

    // Posiciona o ponteiro de leitura no início dos registros (após o
    // cabeçalho) do arquivo 2
    fseek(f_bin2, HEADER_SIZE, SEEK_SET);

    // Itera sobre todos os registros do segundo arquivo
    for (int RRN2 = 0; RRN2 < total_records2; RRN2++) {

      // Lê os registros do segundo arquivo
      if (!data_record_read(f_bin2, &record2)) {
        file_processing_failure_join(&f_bin1, &f_bin2);
        return;
      }

      // Ignora registros que foram removidos logicamente
      if (record2.removido == '1') {
        continue;
      }

      // Verifica se encontrou a chave única codEstacao no segundo arquivo
      if (record1.codProxEstacao == record2.codEstacao) {

        found = true;

        // Imprime os dados unidos
        printf("%d ", record1.codEstacao);

        printf("%s ", record1.nomeEstacao);

        if (strlen(record1.nomeLinha) == 0)
          printf("NULO ");
        else
          printf("%s ", record1.nomeLinha);

        printf("%d ", record1.codProxEstacao);

        printf("%s\n", record2.nomeEstacao);

        // Como codEstacao é único, interrompemos a busca no arquivo 2
        break;
      }
    }
  }

  // Caso não ache nenhum par, exibe uma mensagem para o usuário
  if (!found) {
    printf("Registro inexistente.\n");
  }

  // Salva e fecha os arquivos
  fclose(f_bin1);
  fclose(f_bin2);
}
