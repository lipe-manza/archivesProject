#include <stdio.h>
#include <string.h>

#include "../../include/IO.h"
#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include "../../include/hash_tables.h"
#include "../../include/sql_functions.h"

// Chamada caso haja alguma falha no processamento. Libera a memória das
// hashtables e fecha os arquivos abertos antes de imprimir a mensagem de erro.
void file_processing_failure(FILE **f_csv, FILE **f_bin, HashEstacao **hash_est,
                             HashPar **hash_par) {
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

  // Instancia na stack o cabeçalho
  DataHeader header = {'0', -1, 0, 0, 0};

  // Lê os nomes dos arquivos .csv e .bin da entrada padrão
  char csv_name[50];
  char bin_name[50];
  if (scanf("%s %s", csv_name, bin_name) != 2) {
    file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par);
    return;
  }

  // Inicializa as tabelas hash para contar estações e pares de estações únicos
  hash_est = criar_hash_estacao();
  hash_par = criar_hash_par();

  // Aborta se a alocação das tabelas hash falhar
  if (hash_est == NULL || hash_par == NULL) {
    file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par);
    return;
  }

  // Abre o arquivo .csv para leitura
  f_csv = fopen(csv_name, "r");
  if (f_csv == NULL) {
    file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par);
    return;
  }

  // Cria o arquivo .bin com modo de escrita binária ("wb"), e marca como
  // inconsistente o status
  f_bin = open_binary_file(bin_name, "wb");
  if (f_bin == NULL) {
    file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par);
    return;
  }

  // Escreve o cabeçalho inicial inconsistente no arquivo binário
  data_header_write(f_bin, &header);

  char buffer[256];

  // Pula a primeira linha do CSV (linha de cabeçalho do arquivo texto)
  if (fgets(buffer, sizeof(buffer), f_csv) == NULL) {
    file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par);
    return;
  }

  // Lê o arquivo CSV linha por linha e processa cada registro
  while (fgets(buffer, sizeof(buffer), f_csv) != NULL) {
    // Trunca a string lida para remover \r e \n
    buffer[strcspn(buffer, "\r\n")] = '\0';

    char *p = buffer;
    char *token;

    // Reseta o status de removido e o ponteiro de próximo por segurança
    DataRecord record = {0};
    record.removido = '0';
    record.proximo = -1;

    // Tokeniza a linha lida usando strsep com delimitador vírgula (',')

    // 1. codEstacao
    token = strsep(&p, ",");
    if (token == NULL) {
      file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par);
      return;
    }
    record.codEstacao = safe_atoi(token, -1);

    // 2. nomeEstacao
    token = strsep(&p, ",");
    if (token == NULL) {
      file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par);
      return;
    }
    record.tamNomeEstacao = strlen(token);
    strncpy(record.nomeEstacao, token, sizeof(record.nomeEstacao) - 1);
    record.nomeEstacao[sizeof(record.nomeEstacao) - 1] = '\0';

    // 3. codLinha
    token = strsep(&p, ",");
    if (token == NULL) {
      file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par);
      return;
    }
    record.codLinha = safe_atoi(token, -1);

    // 4. nomeLinha
    token = strsep(&p, ",");
    if (token == NULL || strlen(token) == 0) {
      record.tamNomeLinha = 0;
      record.nomeLinha[0] = '\0';
    } else {
      record.tamNomeLinha = strlen(token);
      strncpy(record.nomeLinha, token, sizeof(record.nomeLinha) - 1);
      record.nomeLinha[sizeof(record.nomeLinha) - 1] = '\0';
    }

    // 5. codProxEstacao
    token = strsep(&p, ",");
    if (token == NULL) {
      file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par);
      return;
    }
    record.codProxEstacao = safe_atoi(token, -1);

    // 6. distProxEstacao
    token = strsep(&p, ",");
    if (token == NULL) {
      file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par);
      return;
    }
    record.distProxEstacao = safe_atoi(token, -1);

    // 7. codLinhaIntegra
    token = strsep(&p, ",");
    if (token == NULL) {
      file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par);
      return;
    }
    record.codLinhaIntegra = safe_atoi(token, -1);

    // 8. codEstIntegra
    token = strsep(&p, ",");
    if (token == NULL) {
      file_processing_failure(&f_csv, &f_bin, &hash_est, &hash_par);
      return;
    }
    token[strcspn(token, "\r\n")] = '\0';
    record.codEstIntegra = safe_atoi(token, -1);

    // Escreve o registro preenchido no arquivo binário
    data_record_write(f_bin, &record);

    // Insere nas tabelas hash para rastrear entradas únicas
    inserir_estacao(hash_est, record.nomeEstacao);
    inserir_par(hash_par, record.codEstacao, record.codProxEstacao);

    // Incrementa o proxRRN no cabeçalho
    header.proxRRN++;
  }

  // Atualiza os contadores finais no cabeçalho após varrer todo o CSV
  header.nroEstacoes = get_nro_estacoes(hash_est);
  header.nroParesEstacoes = get_nro_pares(hash_par);

  // Marca o arquivo como consistente ('1') e reescreve o cabeçalho atualizado
  header.status = '1';
  data_header_write(f_bin, &header);

  // Fecha arquivos e libera a memória das hashtables
  fclose(f_csv);
  fclose(f_bin);
  free_hash_estacao(hash_est);
  free_hash_par(hash_par);

  // Exibe o arquivo binário na tela utilizando o código fornecido pelo
  // run.codes
  BinarioNaTela(bin_name);
}
