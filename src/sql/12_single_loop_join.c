#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../../include/IO.h"
#include "../../include/btree.h"
#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include "../../include/sql_functions.h"

// Função auxiliar para fechamento de múltiplos arquivos e exibição de erro.
// Evita vazamento de memória e handles soltos quando a operação é abortada.
void file_processing_failure_single_join(FILE **f_bin1, FILE **f_bin2,
                                         FILE **f_idx) {
  if (f_bin1 != NULL && *f_bin1 != NULL) {
    fclose(*f_bin1);
    *f_bin1 = NULL;
  }
  if (f_bin2 != NULL && *f_bin2 != NULL) {
    fclose(*f_bin2);
    *f_bin2 = NULL;
  }
  if (f_idx != NULL && *f_idx != NULL) {
    fclose(*f_idx);
    *f_idx = NULL;
  }

  printf("Falha no processamento do arquivo.\n");
}

// Realiza a junção entre dois arquivos usando a igualdade de codProxEstacao e
// codEstacao. O arquivo 2 é acessado diretamente via índice Árvore-B para
// otimização da busca.
void single_loop_join() {
  FILE *f_bin1 = NULL;
  FILE *f_bin2 = NULL;
  FILE *f_idx = NULL;

  DataHeader header1, header2;
  BTreeHeader header_idx;
  DataRecord record1, record2;

  char bin_name1[50], field1[50];
  char bin_name2[50], field2[50];
  char idx_name2[50];

  // Lê os nomes dos arquivos e os campos que serão utilizados na busca e junção
  if (scanf("%s %s", bin_name1, field1) != 2) {
    file_processing_failure_single_join(&f_bin1, &f_bin2, &f_idx);
    return;
  }

  if (scanf("%s %s", bin_name2, field2) != 2) {
    file_processing_failure_single_join(&f_bin1, &f_bin2, &f_idx);
    return;
  }

  if (scanf("%s", idx_name2) != 1) {
    file_processing_failure_single_join(&f_bin1, &f_bin2, &f_idx);
    return;
  }

  // Abre os arquivos de dados requeridos para a leitura
  f_bin1 = open_binary_file(bin_name1, "rb");
  if (f_bin1 == NULL) {
    file_processing_failure_single_join(&f_bin1, &f_bin2, &f_idx);
    return;
  }

  f_bin2 = open_binary_file(bin_name2, "rb");
  if (f_bin2 == NULL) {
    file_processing_failure_single_join(&f_bin1, &f_bin2, &f_idx);
    return;
  }

  // Abre o arquivo de índice da Árvore-B
  f_idx = open_binary_file(idx_name2, "rb");
  if (f_idx == NULL) {
    file_processing_failure_single_join(&f_bin1, &f_bin2, &f_idx);
    return;
  }

  // Valida o cabeçalho dos arquivos de dados
  if (!data_header_read(f_bin1, &header1) ||
      !data_header_read(f_bin2, &header2)) {
    file_processing_failure_single_join(&f_bin1, &f_bin2, &f_idx);
    return;
  }

  // Valida o cabeçalho do arquivo de índice
  if (!btree_header_read(f_idx, &header_idx)) {
    file_processing_failure_single_join(&f_bin1, &f_bin2, &f_idx);
    return;
  }

  bool found = false;
  int total_records1 = header1.proxRRN;

  // Posiciona o ponteiro de leitura no início dos registros (após o cabeçalho)
  fseek(f_bin1, HEADER_SIZE, SEEK_SET);

  // Itera somente sobre os registros do primeiro arquivo atuando como laço
  // externo
  for (int rrn1 = 0; rrn1 < total_records1; rrn1++) {

    if (!data_record_read(f_bin1, &record1)) {
      file_processing_failure_single_join(&f_bin1, &f_bin2, &f_idx);
      return;
    }

    // Ignora completamente registros marcados como removidos
    if (record1.removido == '1') {
      continue;
    }

    // A busca indexada só é feita se o campo possuir valor válido para
    // comparação
    if (record1.codProxEstacao != -1) {
      // Procura a chave na Árvore-B que retorna o byte offset do registro
      // correspondente
      int offset2 =
          btree_search_key(f_idx, &header_idx, record1.codProxEstacao);

      // Lê o registro de forma direta quando a chave for encontrada no índice
      if (offset2 != BTREE_NOT_FOUND) {
        fseek(f_bin2, offset2, SEEK_SET);

        if (!data_record_read(f_bin2, &record2)) {
          file_processing_failure_single_join(&f_bin1, &f_bin2, &f_idx);
          return;
        }

        // Valida se o registro lido via índice também atende aos critérios
        // operacionais
        if (record2.removido != '1' && record2.codEstacao != -1 &&
            record1.codProxEstacao == record2.codEstacao) {

          found = true;

          // Imprime o cruzamento de dados protegendo campos nulos ou vazios
          if (record1.codEstacao == -1)
            printf("NULO ");
          else
            printf("%d ", record1.codEstacao);

          if (strlen(record1.nomeEstacao) == 0)
            printf("NULO ");
          else
            printf("%s ", record1.nomeEstacao);

          if (strlen(record1.nomeLinha) == 0)
            printf("NULO ");
          else
            printf("%s ", record1.nomeLinha);

          if (record1.codProxEstacao == -1)
            printf("NULO ");
          else
            printf("%d ", record1.codProxEstacao);

          // O nome da próxima estação é extraído do registro associado
          if (strlen(record2.nomeEstacao) == 0)
            printf("NULO\n");
          else
            printf("%s\n", record2.nomeEstacao);
        }
      }
    }
  }

  // Avisa o usuário caso não houver nenhuma combinação entre os arquivos
  if (!found) {
    printf("Registro inexistente.\n");
  }

  // Salva e fecha todos os arquivos abertos
  fclose(f_bin1);
  fclose(f_bin2);
  fclose(f_idx);
}
