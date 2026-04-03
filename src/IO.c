#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/IO.h"


void read_from_bin(FILE *p_bin, REG *reg)
{
    fread(&reg->removido, sizeof(reg->removido), 1, p_bin);
    fread(&reg->proximo, sizeof(reg->proximo), 1, p_bin);
    fread(&reg->codEstacao, sizeof(reg->codEstacao), 1, p_bin);
    fread(&reg->codLinha, sizeof(reg->codLinha), 1, p_bin);
    fread(&reg->codProxEstacao, sizeof(reg->codProxEstacao), 1, p_bin);
    fread(&reg->distProxEstacao, sizeof(reg->distProxEstacao), 1, p_bin);
    fread(&reg->codLinhaIntegra, sizeof(reg->codLinhaIntegra), 1, p_bin);
    fread(&reg->codEstIntegra, sizeof(reg->codEstIntegra), 1, p_bin);

    fread(&reg->tamNomeEstacao, sizeof(reg->tamNomeEstacao), 1, p_bin);
    if (reg->tamNomeEstacao > 0)
    {
        fread(reg->nomeEstacao, sizeof(char), reg->tamNomeEstacao, p_bin);
        reg->nomeEstacao[reg->tamNomeEstacao] = '\0'; // coloca \0 na string
    }
    else
        reg->nomeEstacao[0] = '\0';

    fread(&reg->tamNomeLinha, sizeof(reg->tamNomeLinha), 1, p_bin);
    if (reg->tamNomeLinha > 0)
    {
        fread(reg->nomeLinha, sizeof(char), reg->tamNomeLinha, p_bin);
        reg->nomeLinha[reg->tamNomeLinha] = '\0'; // coloca \0 na string
    }
    else
        reg->nomeLinha[0] = '\0';
}

void write_in_bin(FILE *p_bin, REG *reg)
{

    fwrite(&reg->removido, sizeof(reg->removido), 1, p_bin);
    fwrite(&reg->proximo, sizeof(reg->proximo), 1, p_bin);
    fwrite(&reg->codEstacao, sizeof(reg->codEstacao), 1, p_bin);
    fwrite(&reg->codLinha, sizeof(reg->codLinha), 1, p_bin);
    fwrite(&reg->codProxEstacao, sizeof(reg->codProxEstacao), 1, p_bin);
    fwrite(&reg->distProxEstacao, sizeof(reg->distProxEstacao), 1, p_bin);
    fwrite(&reg->codLinhaIntegra, sizeof(reg->codLinhaIntegra), 1, p_bin);
    fwrite(&reg->codEstIntegra, sizeof(reg->codEstIntegra), 1, p_bin);

    fwrite(&reg->tamNomeEstacao, sizeof(reg->tamNomeEstacao), 1, p_bin);
    if (reg->tamNomeEstacao > 0)
        fwrite(reg->nomeEstacao, sizeof(char), reg->tamNomeEstacao, p_bin);

    fwrite(&reg->tamNomeLinha, sizeof(reg->tamNomeLinha), 1, p_bin);
    if (reg->tamNomeLinha > 0)
        fwrite(reg->nomeLinha, sizeof(char), reg->tamNomeLinha, p_bin);

    char lixo = '$';
    int bytes_usados = 37 + reg->tamNomeEstacao + reg->tamNomeLinha;
    int lixo_size = 80 - bytes_usados;

    for (int i = 0; i < lixo_size; i++)
    {
        fwrite(&lixo, sizeof(char), 1, p_bin);
    }
}

void print_registro_in_terminal(REG *registro)
{
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
void BinarioNaTela(char *arquivo)
{
    FILE *fs;
    if (arquivo == NULL || !(fs = fopen(arquivo, "rb")))
    {
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
    for (unsigned long i = 0; i < fl; i++)
    {
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
void ScanQuoteString(char *str)
{
    char R;

    while ((R = getchar()) != EOF && isspace(R))
        ; // ignorar espaços, \r, \n...

    if (R == 'N' || R == 'n')
    { // campo NULO
        getchar();
        getchar();
        getchar();       // ignorar o "ULO" de NULO.
        strcpy(str, ""); // copia string vazia
    }
    else if (R == '\"')
    {
        if (scanf("%[^\"]", str) != 1)
        { // ler até o fechamento das aspas
            strcpy(str, "");
        }
        getchar(); // ignorar aspas fechando
    }
    else if (R != EOF)
    { // vc tá tentando ler uma string que não tá entre
      // aspas! Fazer leitura normal %s então, pois deve
      // ser algum inteiro ou algo assim...
        // str[0] = R;
        // scanf("%s", &str[1]);

        // Devolve o caractere para o stdin
        ungetc(R, stdin);
        scanf("%s", str);
    }
    else
    { // EOF
        strcpy(str, "");
    }
}

