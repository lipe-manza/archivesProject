#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../headers/IO.h"

FILE *open_bin(char *bin_name, char *mode) {
  // Tenta abrir o arquivo binário para mode
  FILE *f_bin = fopen(bin_name, mode);

  // Verifica se o arquivo pode ser aberto
  if (f_bin == NULL) {
    printf("Falha no processamento do arquivo.");
    return NULL;
  }

  // Verifica se o arquivo não está sendo aberto para criação
  if (mode[0] != 'w') {
    char status = '0';

    fread(&status, sizeof(char), 1, f_bin);

    // Se o status estiver inconsistente, o arquivo não pode ser usado
    if (status == '0') {
      printf("Falha no processamento do arquivo");
      return NULL;
    }
  }

  fseek(f_bin, -1, SEEK_CUR);

  return f_bin;
}

void tornar_inconsistente(FILE *f_bin) {
  long pos = ftell(f_bin);
  char status = '0';

  fwrite(&status, sizeof(char), 1, f_bin);
  fflush(f_bin);

  fseek(f_bin, pos, SEEK_SET);
}

void print_registro_in_terminal(REG *registro) {
  // Nao podem ser nulos
  printf("%d ", registro->codEstacao);
  printf("%s ", registro->nomeEstacao);

  // Código da Linha
  if (registro->codLinha == -1)
    printf("NULO ");
  else
    printf("%d ", registro->codLinha);

  // Nome da Linha
  if (registro->tamNomeLinha == 0)
    printf("NULO ");
  else
    printf("%s ", registro->nomeLinha);

  // Código da próxima estação
  if (registro->codProxEstacao == -1)
    printf("NULO ");
  else
    printf("%d ", registro->codProxEstacao);

  // Distância da próxima estação
  if (registro->distProxEstacao == -1)
    printf("NULO ");
  else
    printf("%d ", registro->distProxEstacao);

  // Código da linha integrante
  if (registro->codLinhaIntegra == -1)
    printf("NULO ");
  else
    printf("%d ", registro->codLinhaIntegra);

  // Código da Estação que faz a integrante
  if (registro->codEstIntegra == -1)
    printf("NULO");
  else
    printf("%d", registro->codEstIntegra);

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

void read_new_registro_from_terminal(REG *new_registro) {
  char str[40];

  // Le o codEstacao
  ScanQuoteString(str);
  new_registro->codEstacao = strlen(str) > 0 ? atoi(str) : -1;

  // Le o codEstacao
  ScanQuoteString(str);
  new_registro->tamNomeEstacao = strlen(str);
  strcpy(new_registro->nomeEstacao, str);

  // Le o codLinha
  ScanQuoteString(str);
  new_registro->codLinha = strlen(str) > 0 ? atoi(str) : -1;

  // Le o nomeLinha
  ScanQuoteString(str);
  new_registro->tamNomeLinha = strlen(str);
  strcpy(new_registro->nomeLinha, str);

  // Le o codProxEstacao
  ScanQuoteString(str);
  new_registro->codProxEstacao = strlen(str) > 0 ? atoi(str) : -1;

  // Le o distProxEstacao
  ScanQuoteString(str);
  new_registro->distProxEstacao = strlen(str) > 0 ? atoi(str) : -1;

  // Le o codLinhaIntegra
  ScanQuoteString(str);
  new_registro->codLinhaIntegra = strlen(str) > 0 ? atoi(str) : -1;

  // Le o codEstIntegra
  ScanQuoteString(str);
  new_registro->codEstIntegra = strlen(str) > 0 ? atoi(str) : -1;

  return;
}

// Se a string não for vazia, retorna o atoi
// Caso contrário retorna o valor padrão fornecido
int satoi(char *string, int val) {
  return strlen(string) > 0 ? atoi(string) : val;
}
