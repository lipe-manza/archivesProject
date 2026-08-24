#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/IO.h"

FILE *open_binary_file(char *bin_name, char *mode) {
  // Tenta abrir o arquivo binário com o modo especificado
  FILE *f_bin = fopen(bin_name, mode);

  // Verifica se o arquivo pôde ser aberto
  if (f_bin == NULL) {
    return NULL;
  }

  char status = '0';
  // Verifica se o arquivo não está sendo aberto para criação
  if (mode[0] != 'w') {
    fread(&status, sizeof(char), 1, f_bin);

    // Se o status estiver inconsistente, o arquivo não pode ser usado
    if (status == '0') {
      fclose(f_bin);
      return NULL;
    }
  }

  // Se o arquivo for aberto apenas para leitura, não muda o status
  if (strcmp(mode, "rb") != 0) {
    status = '0';
    fseek(f_bin, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 0, f_bin);
    fflush(f_bin);
  }

  // Retorna com segurança para o início do arquivo
  fseek(f_bin, 0, SEEK_SET);
  return f_bin;
}

void display_data_record(const DataRecord *record) {
  if (record == NULL)
    return;

  // Nao podem ser nulos
  printf("%d ", record->codEstacao);
  printf("%s ", record->nomeEstacao);

  // Código da Linha
  int line_code = record->codLinha;
  if (line_code == -1)
    printf("NULO ");
  else
    printf("%d ", line_code);

  // Nome da Linha
  const char *line_name = record->nomeLinha;
  if (line_name == NULL || strlen(line_name) == 0)
    printf("NULO ");
  else
    printf("%s ", line_name);

  // Código da próxima estação
  int next_station_code = record->codProxEstacao;
  if (next_station_code == -1)
    printf("NULO ");
  else
    printf("%d ", next_station_code);

  // Distância da próxima estação
  int next_station_dist = record->distProxEstacao;
  if (next_station_dist == -1)
    printf("NULO ");
  else
    printf("%d ", next_station_dist);

  // Código da linha integrante
  int integ_line_code = record->codLinhaIntegra;
  if (integ_line_code == -1)
    printf("NULO ");
  else
    printf("%d ", integ_line_code);

  // Código da Estação que faz a integrante
  int integ_station_code = record->codEstIntegra;
  if (integ_station_code == -1)
    printf("NULO");
  else
    printf("%d", integ_station_code);

  printf("\n");
}

/*
 * Você não precisa entender o código dessa função.
 *
 * Use essa função para comparação no run.codes.
 * Lembre-se de ter fechado (fclose) o arquivo anteriormente.
 *
 * Ela vai abrir de novo para leitura e depois fechar
 * (você não vai perder pontos por isso se usar ela).
 */
void BinarioNaTela(char *arquivo) {
  FILE *fs;
  if (arquivo == NULL || !(fs = fopen(arquivo, "rb"))) {
    fprintf(stderr,
            "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): "
            "não foi possível abrir o arquivo que me passou para leitura. "
            "Ele existe e você tá passando o nome certo? Você lembrou de "
            "fechar ele com fclose depois de usar?\n");
    return;
  }

  fseek(fs, 0, SEEK_END);
  size_t fl = ftell(fs);

  fseek(fs, 0, SEEK_SET);
  unsigned char *mb = (unsigned char *)malloc(fl);
  fread(mb, 1, fl, fs);

  unsigned long cs = 0;
  for (unsigned long i = 0; i < fl; i++) {
    cs += (unsigned long)mb[i];
  }

  printf("%lf\n", (cs / (double)100));

  free(mb);
  fclose(fs);
}

/*
 *	Use essa função para ler um campo string delimitado entre aspas (").
 *	Chame ela na hora que for ler tal campo. Por exemplo:
 *
 *	A entrada está da seguinte forma:
 *		nomeDoCampo "MARIA DA SILVA"
 *
 *	Para ler isso para as strings já alocadas str1 e str2 do seu programa,
 * você faz: scanf("%s", str1); // Vai salvar nomeDoCampo em str1
 *		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2
 * (sem as aspas)
 *
 */
void ScanQuoteString(char *str) {
  char R;

  while ((R = getchar()) != EOF && isspace(R))
    ; // ignorar espaços, \r, \n...

  if (R == 'N' || R == 'n') { // campo NULO
    getchar();
    getchar();
    getchar();       // ignorar o "ULO" de NULO.
    strcpy(str, ""); // copia string vazia
  } else if (R == '\"') {
    if (scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
      strcpy(str, "");
    }
    getchar();           // ignorar aspas fechando
  } else if (R != EOF) { // vc tá tentando ler uma string que não tá entre
                         // aspas! Fazer leitura normal %s então, pois deve
                         // ser algum inteiro ou algo assim...
    // str[0] = R;
    // scanf("%s", &str[1]);

    // Devolve o caractere para o stdin
    ungetc(R, stdin);
    if (scanf("%s", str) != 1)
      strcpy(str, "");
  } else { // EOF
    strcpy(str, "");
  }
}

// Lê a inserção pedida e grava no new_record utilizando ScanQuoteString e
// fazendo as devidas alterações para quando for pedido NULO
void read_data_record_from_stdin(DataRecord *new_record) {
  if (new_record == NULL)
    return;

  char str[51];

  // Lê codEstacao
  ScanQuoteString(str);
  new_record->codEstacao = strlen(str) > 0 ? atoi(str) : -1;

  // Lê nomeEstacao
  ScanQuoteString(str);
  strcpy(new_record->nomeEstacao, str);
  new_record->tamNomeEstacao = strlen(str);

  // Lê codLinha
  ScanQuoteString(str);
  new_record->codLinha = strlen(str) > 0 ? atoi(str) : -1;

  // Lê nomeLinha
  ScanQuoteString(str);
  strcpy(new_record->nomeLinha, str);
  new_record->tamNomeLinha = strlen(str);

  // Lê codProxEstacao
  ScanQuoteString(str);
  new_record->codProxEstacao = strlen(str) > 0 ? atoi(str) : -1;

  // Lê distProxEstacao
  ScanQuoteString(str);
  new_record->distProxEstacao = strlen(str) > 0 ? atoi(str) : -1;

  // Lê codLinhaIntegra
  ScanQuoteString(str);
  new_record->codLinhaIntegra = strlen(str) > 0 ? atoi(str) : -1;

  // Lê codEstIntegra
  ScanQuoteString(str);
  new_record->codEstIntegra = strlen(str) > 0 ? atoi(str) : -1;
}

int safe_atoi(char *string, int val) {
  // Se a string não for vazia, retorna o atoi
  // Caso contrário retorna o valor padrão fornecido
  return strlen(string) > 0 ? atoi(string) : val;
}
