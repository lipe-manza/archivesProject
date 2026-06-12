#include <string.h>

#include "../../headers/IO.h"
#include "../../headers/hash_tables.h"
#include "../../headers/registro.h"
#include "../../headers/sql_functions.h"

// Função auxiliar para evitar repetição quando há falha no processamento do
// arquivo
void falha_processamento_arquivo(FILE **f1, FILE **f2, HashEstacao **hash_est,
                                 HashPar **hash_par) {
  if (f1 != NULL && *f1 != NULL) {
    fclose(*f1);
    *f1 = NULL;
  }
  if (f2 != NULL && *f2 != NULL) {
    fclose(*f2);
    *f2 = NULL;
  }

  if (hash_est != NULL)
    free_hash_estacao(*hash_est);

  if (hash_par != NULL)
    free_hash_par(*hash_par);

  printf("Falha no processamento do arquivo.");
}

// Função principal para converter o arquivo .csv para .bin
void create_table() {
  FILE *f_csv = NULL;
  FILE *f_bin = NULL;
  HashEstacao *hash_est = NULL;
  HashPar *hash_par = NULL;

  // Leitura dos nomes dos arquivos .csv e .bin
  char bin_name[50];
  char csv_name[50];
  if (scanf("%s %s", csv_name, bin_name) != 2)
    return;

  // Cria as hashtables para contar as estações e pares de estações únicas
  hash_est = criar_hash_estacao();
  hash_par = criar_hash_par();

  // Encerra o programa em caso de falha de alocação de alguma das hashtables
  if (hash_est == NULL || hash_par == NULL) {
    falha_processamento_arquivo(&f_csv, &f_bin, &hash_est, &hash_par);
    return;
  }

  // Abertura do arquivo .csv para leitura
  f_csv = fopen(csv_name, "r");
  if (f_csv == NULL) {
    falha_processamento_arquivo(&f_csv, &f_bin, &hash_est, &hash_par);
    return;
  }

  // Criação do arquivo .bin com escrita binária
  f_bin = open_bin(bin_name, "wb");
  if (f_bin == NULL) {
    falha_processamento_arquivo(&f_csv, &f_bin, &hash_est, &hash_par);
    return;
  }

  tornar_inconsistente(f_bin);

  // Constrói e escreve o cabeçalho no arquivo
  CAB cabecalho;

  // status = 0; topo = -1; proxRRN = 0; nroEstacoes = 0; nroParesEstacao = 0;
  construir_cab(&cabecalho, '0', -1, 0, 0, 0);

  escrever_cab_bin(f_bin, &cabecalho);

  // Variáveis auxiliares
  char buffer[256];

  REG registro;

  // Pula a linha de cabeçalho do arquivo .csv
  if (fgets(buffer, sizeof(buffer), f_csv) == NULL) {
    falha_processamento_arquivo(&f_csv, &f_bin, &hash_est, &hash_par);
    return;
  }

  // Lê o arquivo CSV linha por linha e processa cada registro escrevendo no
  // arquivo binário
  while (fgets(buffer, sizeof(buffer), f_csv) != NULL) {
    // Trunca a linha lida para remover o \r e o \n
    buffer[strcspn(buffer, "\r\n")] = '\0';

    // Variáveis para tokenização da linha lida
    char *p = buffer;
    char *token;

    // Inicializa os campos removido e próximo
    registro.removido = '0';
    registro.proximo = -1;

    // Tokeniza a linha lida usando strsep e separa os campos usando a
    // vírgula como delimitador

    // Transforma o primeiro token (código da estação) de string para
    // inteiro e salva no registro auxiliar
    token = strsep(&p, ",");
    if (token == NULL) {
      falha_processamento_arquivo(&f_csv, &f_bin, &hash_est, &hash_par);
      return;
    }
    registro.codEstacao = satoi(token, -1);

    // Processa o segundo token (nome da estação)
    // e salva o tamanho e a string no registro auxiliar
    token = strsep(&p, ",");
    if (token == NULL) {
      falha_processamento_arquivo(&f_csv, &f_bin, &hash_est, &hash_par);
      return;
    }
    registro.tamNomeEstacao = strlen(token);
    strcpy(registro.nomeEstacao, token);

    // Transforma o terceiro token (código da linha) de string para inteiro
    // e salva no registro auxiliar
    token = strsep(&p, ",");
    if (token == NULL) {
      falha_processamento_arquivo(&f_csv, &f_bin, &hash_est, &hash_par);
      return;
    }
    registro.codLinha = satoi(token, -1);

    // Processa o quarto token (nome da linha)
    // e salva o tamanho e a string no registro auxiliar
    token = strsep(&p, ",");
    if (token == NULL) {
      registro.tamNomeLinha = 0;
      registro.nomeLinha[0] = '\0';
    } else {
      registro.tamNomeLinha = strlen(token);
      strcpy(registro.nomeLinha, token);
    }

    // Transforma o quinto token (código da próxima estação) de string para
    // inteiro e salva no registro auxiliar
    token = strsep(&p, ",");
    if (token == NULL) {
      falha_processamento_arquivo(&f_csv, &f_bin, &hash_est, &hash_par);
      return;
    }
    registro.codProxEstacao = satoi(token, -1);

    // Transforma o sexto token (distância para a próxima estação) de string
    // para inteiro e salva no registro auxiliar
    token = strsep(&p, ",");
    if (token == NULL) {
      falha_processamento_arquivo(&f_csv, &f_bin, &hash_est, &hash_par);
      return;
    }
    registro.distProxEstacao = satoi(token, -1);

    // Transforma o sétimo token (código da linha de integração) de string
    // para inteiro E salva no registro auxiliar
    token = strsep(&p, ",");
    if (token == NULL) {
      falha_processamento_arquivo(&f_csv, &f_bin, &hash_est, &hash_par);
      return;
    }
    registro.codLinhaIntegra = satoi(token, -1);

    // Transforma o oitavo token (código da estação de integração) de string
    // para inteiro E salva no registro auxiliar
    token = strsep(&p, ",");
    if (token == NULL) {
      falha_processamento_arquivo(&f_csv, &f_bin, &hash_est, &hash_par);
      return;
    }
    // Limpa o último token, caso ainda tenha sobrado quebras de linha
    token[strcspn(token, "\r\n")] = '\0';
    registro.codEstIntegra = satoi(token, -1);

    // Escreve o registro no arquivo binário
    escrever_reg_bin(f_bin, &registro);

    inserir_estacao(hash_est, registro.nomeEstacao);
    inserir_par(hash_par, registro.codEstacao, registro.codProxEstacao);

    cabecalho.proxRRN++;
  }

  // Atualização dos campos do cabeçalho
  cabecalho.nroEstacoes = get_nro_estacoes(hash_est);
  cabecalho.nroParesEstacoes = get_nro_pares(hash_par);

  // Atualiza e escreve o cabeçalho
  cabecalho.status = '1';
  escrever_cab_bin(f_bin, &cabecalho);

  // Fecha os arquivos e desaloca as hashtables
  fclose(f_csv);
  f_csv = NULL;

  fclose(f_bin);
  f_bin = NULL;

  free_hash_estacao(hash_est);
  hash_est = NULL;

  free_hash_par(hash_par);
  hash_par = NULL;

  BinarioNaTela(bin_name);
}
