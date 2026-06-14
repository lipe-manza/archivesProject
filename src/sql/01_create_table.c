#include <stdio.h>
#include <string.h>

#include "../../include/IO.h"
#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include "../../include/hash_tables.h"
#include "../../include/sql_functions.h"

// Função auxiliar para evitar repetição de código em caso de falha no
// processamento do arquivo. Libera toda a memória alocada e fecha os arquivos
// abertos antes de imprimir a mensagem de erro.
void file_processing_failure(FILE **f_csv, FILE **f_bin, HashEstacao **hash_est,
                             HashPar **hash_par, DataHeader **header,
                             DataRecord **record) {
  if (f_csv != NULL && *f_csv != NULL) {
    fclose(*f_csv);
    *f_csv = NULL;
  }
  if (f_bin != NULL && *f_bin != NULL) {
    fclose(*f_bin);
    *f_bin = NULL;
  }
  if (hash_est != NULL && *hash_est != NULL) {
    free_hash_estacao(*hash_est);
    *hash_est = NULL;
  }
  if (hash_par != NULL && *hash_par != NULL) {
    free_hash_par(*hash_par);
    *hash_par = NULL;
  }
  if (header != NULL) {
    data_header_destroy(header);
  }
  if (record != NULL) {
    data_record_destroy(record);
  }

  printf("Falha no processamento do arquivo.\n");
}

// Função principal para converter o arquivo .csv de entrada em um arquivo
// binário .bin. Lê os dados sequencialmente, popula os registros de dados e
// indexa as estações e pares únicos.
void create_table() {
  FILE *f_csv = NULL;
  FILE *f_bin = NULL;
  HashEstacao *hash_est = NULL;
  HashPar *hash_par = NULL;
  DataHeader *header = NULL;
  DataRecord *record = NULL;

  // Lê os nomes dos arquivos .csv e .bin da entrada padrão
  char csv_name[50];
  char bin_name[50];
  if (scanf("%s %s", csv_name, bin_name) != 2) {
    file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par, &header,
                            &record);
    return;
  }

  // Inicializa as tabelas hash para contar estações e pares de estações únicos
  hash_est = criar_hash_estacao();
  hash_par = criar_hash_par();

  // Aborta se a alocação das tabelas hash falhar
  if (hash_est == NULL || hash_par == NULL) {
    file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par, &header,
                            &record);
    return;
  }

  // Abre o arquivo .csv para leitura
  f_csv = fopen(csv_name, "r");
  if (f_csv == NULL) {
    file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par, &header,
                            &record);
    return;
  }

  // Cria o arquivo .bin com modo de escrita binária ("wb")
  f_bin = open_binary_file(bin_name, "wb");
  if (f_bin == NULL) {
    file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par, &header,
                            &record);
    return;
  }

  // Marca o arquivo como inconsistente ('0') logo após a abertura e força a
  // gravação no disco com fflush, conforme exigido.
  mark_file_inconsistent(f_bin);

  // Instancia o cabeçalho (inicia com status inconsistente '0' por padrão)
  header = data_header_create();
  if (header == NULL) {
    file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par, &header,
                            &record);
    return;
  }

  // Escreve o cabeçalho inicial inconsistente no arquivo binário
  data_header_write(f_bin, header);

  // Instancia o registro de dados que será reutilizado dentro do loop
  record = data_record_create();
  if (record == NULL) {
    file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par, &header,
                            &record);
    return;
  }

  char buffer[256];

  // Pula a primeira linha do CSV (linha de cabeçalho do arquivo texto)
  if (fgets(buffer, sizeof(buffer), f_csv) == NULL) {
    file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par, &header,
                            &record);
    return;
  }

  // Lê o arquivo CSV linha por linha e processa cada registro
  while (fgets(buffer, sizeof(buffer), f_csv) != NULL) {
    // Trunca a string lida para remover \r e \n
    buffer[strcspn(buffer, "\r\n")] = '\0';

    char *p = buffer;
    char *token;

    // Reseta o status de removido e o ponteiro de próximo por segurança
    data_record_set_removido(record, '0');
    data_record_set_proximo(record, -1);

    // Tokeniza a linha lida usando strsep com delimitador vírgula (',')

    // 1. codEstacao
    token = strsep(&p, ",");
    if (token == NULL) {
      file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par, &header,
                              &record);
      return;
    }
    data_record_set_codEstacao(record, safe_atoi(token, -1));

    // 2. nomeEstacao (O setter calcula automaticamente tamNomeEstacao)
    token = strsep(&p, ",");
    if (token == NULL) {
      file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par, &header,
                              &record);
      return;
    }
    data_record_set_nomeEstacao(record, token);

    // 3. codLinha
    token = strsep(&p, ",");
    if (token == NULL) {
      file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par, &header,
                              &record);
      return;
    }
    data_record_set_codLinha(record, safe_atoi(token, -1));

    // 4. nomeLinha (O setter calcula automaticamente tamNomeLinha)
    token = strsep(&p, ",");
    if (token == NULL) {
      data_record_set_nomeLinha(record, "");
    } else {
      data_record_set_nomeLinha(record, token);
    }

    // 5. codProxEstacao
    token = strsep(&p, ",");
    if (token == NULL) {
      file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par, &header,
                              &record);
      return;
    }
    data_record_set_codProxEstacao(record, safe_atoi(token, -1));

    // 6. distProxEstacao
    token = strsep(&p, ",");
    if (token == NULL) {
      file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par, &header,
                              &record);
      return;
    }
    data_record_set_distProxEstacao(record, safe_atoi(token, -1));

    // 7. codLinhaIntegra
    token = strsep(&p, ",");
    if (token == NULL) {
      file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par, &header,
                              &record);
      return;
    }
    data_record_set_codLinhaIntegra(record, safe_atoi(token, -1));

    // 8. codEstIntegra
    token = strsep(&p, ",");
    if (token == NULL) {
      file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par, &header,
                              &record);
      return;
    }
    token[strcspn(token, "\r\n")] = '\0';
    data_record_set_codEstIntegra(record, safe_atoi(token, -1));

    // Escreve o registro preenchido no arquivo binário
    data_record_write(f_bin, record);

    // Insere nas tabelas hash para rastrear entradas únicas
    inserir_estacao(hash_est, data_record_get_nomeEstacao(record));
    inserir_par(hash_par, data_record_get_codEstacao(record),
                data_record_get_codProxEstacao(record));

    // Incrementa o proxRRN no cabeçalho
    int current_rrn = data_header_get_proxRRN(header);
    data_header_set_proxRRN(header, current_rrn + 1);
  }

  // Atualiza os contadores finais no cabeçalho após varrer todo o CSV
  data_header_set_nroEstacoes(header, get_nro_estacoes(hash_est));
  data_header_set_nroParesEstacoes(header, get_nro_pares(hash_par));

  // Marca o arquivo como consistente ('1') e reescreve o cabeçalho atualizado
  data_header_set_status(header, '1');
  data_header_write(f_bin, header);

  // Fecha arquivos e libera toda a memória dinamicamente alocada
  fclose(f_csv);
  fclose(f_bin);
  free_hash_estacao(hash_est);
  free_hash_par(hash_par);
  data_header_destroy(&header);
  data_record_destroy(&record);

  // Exibe o arquivo binário na tela utilizando o código fornecido pelo
  // run.codes
  BinarioNaTela(bin_name);
}
