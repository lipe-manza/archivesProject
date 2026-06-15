#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/IO.h"

FILE *open_binary_file(char *bin_name, char *mode) {
  // Tenta abrir o arquivo binário com o modo especificado
  FILE *f_bin = fopen(bin_name, mode);

  // Verifica se o arquivo pode ser aberto
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

  // Se nao for abrir, apenas para leitura, marca como inconsistente
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

/* void mark_file_inconsistent(FILE *f_bin) { */
/*   if (f_bin == NULL) */
/*     return; */

/*   long pos = ftell(f_bin); */
/*   char status = '0'; */

/*   // Volta para o byte 0 antes de escrever a flag de status inconsistente */
/*   fseek(f_bin, 0, SEEK_SET); */
/*   fwrite(&status, sizeof(char), 1, f_bin); */
/*   fflush(f_bin); */

/*   // Retorna para a posição original onde a função foi chamada */
/*   fseek(f_bin, pos, SEEK_SET); */
/* } */

void display_data_record(const DataRecord *record) {
  if (record == NULL)
    return;

  // Nao podem ser nulos
  printf("%d ", data_record_get_codEstacao(record));
  printf("%s ", data_record_get_nomeEstacao(record));

  // Código da Linha
  int line_code = data_record_get_codLinha(record);
  if (line_code == -1)
    printf("NULO ");
  else
    printf("%d ", line_code);

  // Nome da Linha
  const char *line_name = data_record_get_nomeLinha(record);
  if (line_name == NULL || strlen(line_name) == 0)
    printf("NULO ");
  else
    printf("%s ", line_name);

  // Código da próxima estação
  int next_station_code = data_record_get_codProxEstacao(record);
  if (next_station_code == -1)
    printf("NULO ");
  else
    printf("%d ", next_station_code);

  // Distância da próxima estação
  int next_station_dist = data_record_get_distProxEstacao(record);
  if (next_station_dist == -1)
    printf("NULO ");
  else
    printf("%d ", next_station_dist);

  // Código da linha integrante
  int integ_line_code = data_record_get_codLinhaIntegra(record);
  if (integ_line_code == -1)
    printf("NULO ");
  else
    printf("%d ", integ_line_code);

  // Código da Estação que faz a integrante
  int integ_station_code = data_record_get_codEstIntegra(record);
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
  data_record_set_codEstacao(new_record, strlen(str) > 0 ? atoi(str) : -1);

  // Lê nomeEstacao
  ScanQuoteString(str);
  data_record_set_nomeEstacao(new_record, str);

  // Lê codLinha
  ScanQuoteString(str);
  data_record_set_codLinha(new_record, strlen(str) > 0 ? atoi(str) : -1);

  // Lê nomeLinha
  ScanQuoteString(str);
  data_record_set_nomeLinha(new_record, str);

  // Lê codProxEstacao
  ScanQuoteString(str);
  data_record_set_codProxEstacao(new_record, strlen(str) > 0 ? atoi(str) : -1);

  // Lê distProxEstacao
  ScanQuoteString(str);
  data_record_set_distProxEstacao(new_record, strlen(str) > 0 ? atoi(str) : -1);

  // Lê codLinhaIntegra
  ScanQuoteString(str);
  data_record_set_codLinhaIntegra(new_record, strlen(str) > 0 ? atoi(str) : -1);

  // Lê codEstIntegra
  ScanQuoteString(str);
  data_record_set_codEstIntegra(new_record, strlen(str) > 0 ? atoi(str) : -1);
}

int safe_atoi(char *string, int val) {
  // Se a string não for vazia, retorna o atoi
  // Caso contrário retorna o valor padrão fornecido
  return strlen(string) > 0 ? atoi(string) : val;
}
