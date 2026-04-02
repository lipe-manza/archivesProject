#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/read_bin.h"
#include "../include/fornecidas.h"

typedef struct registro
{
    char removido; // '1' para removido e '0' para nao removido
    int proximo;
    int codEstacao; // Não pode ser nulo
    int codLinha;
    int codProxEstacao;
    int distProxEstacao;
    int codLinhaIntegra;
    int codEstIntegra;
    int tamNomeEstacao;   // Se for 0 não escrever o nomeEstacao
    char nomeEstacao[41]; // Não pode ser nulo
    int tamNomeLinha;
    char nomeLinha[41];
} REG;

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

bool select_from(char *bin_name)
{

    FILE *p_bin = fopen(bin_name, "rb"); // Tenta criar .bin para escrita binaria
    if (p_bin == NULL)
    {
        printf("Falha no processamento do arquivo\n");
        return false;
    }

    char status;
    fread(&status, sizeof(char), 1, p_bin);
    if (status == '0')
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(p_bin);
        return false;
    }

    // Vai para o 5 byte do cabecalho (proxRRN) para pegar quantos registros existem
    fseek(p_bin, 5, SEEK_SET);
    int count_regs = 0;

    fread(&count_regs, sizeof(int), 1, p_bin);

    // Struct registro auxiliar para ler o binario
    REG registro;

    // For que passa por todos os registros gravados no arquivo .bin
    for (int RRN = 0; RRN < count_regs; RRN++)
    {
        // Vai para o primeiro byteoffset do registro de RRN x
        fseek(p_bin, RRN * 80 + 17, SEEK_SET);

        read_from_bin(p_bin, &registro);

        // Verifica se o registro está removido , e se estiver não printa
        if (registro.removido == '0')
            print_registro_in_terminal(&registro);
    }

    if (count_regs == 0)
    {
        printf("Registro inexistente.\n");
    }

    // Fecha os arquivos
    fclose(p_bin);
    p_bin = NULL;

    return true;
}

/*
-----------------------------------------------------------------------------------------------------------------------
*/

/*
Campos do registro (índices):
[0]  codEstacao
[1]  codLinha
[2]  codProxEstacao
[3]  distProxEstacao
[4]  codLinhaIntegra
[5]  codEstIntegra
[6]  tamNomeEstacao
[7]  nomeEstacao
[8]  tamNomeLinha
[9]  nomeLinha
*/

#define SEARCHABLE_FIELDS 10

int field_to_index(char *str)
{
    char *fields[] = {"codEstacao", "codLinha", "codProxEstacao", "distProxEstacao", "codLinhaIntegra", "codEstIntegra", "tamNomeEstacao", "nomeEstacao", "tamNomeLinha", "nomeLinha"};

    for (int i = 0; i < SEARCHABLE_FIELDS; i++)
    {
        if (strcmp(str, fields[i]) == 0)
            return i;
    }

    return -1;
}

void set_gabarito(REG *gabarito, int op, char *str)
{
    switch (op)
    {
    case 0:
        gabarito->codEstacao = (strlen(str) == 0) ? -1 : atoi(str);
        break;
    case 1:
        gabarito->codLinha = (strlen(str) == 0) ? -1 : atoi(str);
        break;
    case 2:
        gabarito->codProxEstacao = (strlen(str) == 0) ? -1 : atoi(str);
        break;
    case 3:
        gabarito->distProxEstacao = (strlen(str) == 0) ? -1 : atoi(str);
        break;
    case 4:
        gabarito->codLinhaIntegra = (strlen(str) == 0) ? -1 : atoi(str);
        break;
    case 5:
        gabarito->codEstIntegra = (strlen(str) == 0) ? -1 : atoi(str);
        break;
    case 6:
        gabarito->tamNomeEstacao = (strlen(str) == 0) ? -1 : atoi(str);
        break;
    case 7:
        strcpy(gabarito->nomeEstacao, str);
        break;
    case 8:
        gabarito->tamNomeLinha = (strlen(str) == 0) ? -1 : atoi(str);
        break;
    case 9:
        strcpy(gabarito->nomeLinha, str);
        break;
    case 10:
        // se existir outro campo, segue o padrão
        break;
    }
}

bool match_gabarito(REG *reg, bool pesquisa[], REG *gabarito)
{
    for (int i = 0; i < SEARCHABLE_FIELDS; i++)
    {
        if (!pesquisa[i])
            continue;

        switch (i)
        {
        case 0:
            if (reg->codEstacao != gabarito->codEstacao)
                return false;
            break;
        case 1:
            if (reg->codLinha != gabarito->codLinha)
                return false;
            break;
        case 2:
            if (reg->codProxEstacao != gabarito->codProxEstacao)
                return false;
            break;
        case 3:
            if (reg->distProxEstacao != gabarito->distProxEstacao)
                return false;
            break;
        case 4:
            if (reg->codLinhaIntegra != gabarito->codLinhaIntegra)
                return false;
            break;
        case 5:
            if (reg->codEstIntegra != gabarito->codEstIntegra)
                return false;
            break;
        case 6:
            if (reg->tamNomeEstacao != gabarito->tamNomeEstacao)
                return false;
            break;
        case 7:
            if (strcmp(reg->nomeEstacao, gabarito->nomeEstacao) != 0)
                return false;
            break;
        case 8:
            if (reg->tamNomeLinha != gabarito->tamNomeLinha)
                return false;
            break;
        case 9:
            if (strcmp(reg->nomeLinha, gabarito->nomeLinha) != 0)
                return false;
            break;
        }
    }

    return true;
}

bool select_from_where(char *bin_name)
{
    int m = 0;
    scanf("%d", &m);
    /*codEstacao; codLinha; codProxEstacao; distProxEstacao; codLinhaIntegra;
    codEstIntegra; tamNomeEstacao; nomeEstacao[41]; tamNomeLinha; nomeLinha[41];*/
    bool pesquisa[SEARCHABLE_FIELDS];
    for (int i = 0; i < SEARCHABLE_FIELDS; i++)
        pesquisa[i] = 0;

    // Struct registro auxiliar para ler o binario
    REG gabarito;

    char str[41];

    for (int i = 0; i < m; i++)
    {
        // le o campo que quer em um buffer
        char field[41];
        scanf("%s", field);
        // jogar esse buffer para o "hash" retorna op
        int op = field_to_index(field);

        if (op == -1)
        {
            printf("Campo não existente.\n");
            return false;
        }

        // Seta como true a pesquisa do campo op
        pesquisa[op] = true;

        // Lê o valor chave
        ScanQuoteString(str);
        
        //
        set_gabarito(&gabarito, op, str);
    }

    FILE *p_bin = fopen(bin_name, "rb"); // Tenta criar .bin para escrita binaria
    if (p_bin == NULL)
    {
        printf("Falha no processamento do arquivo\n");
        return false;
    }

    char status;
    fread(&status, sizeof(char), 1, p_bin);
    if (status == '0')
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(p_bin);
        return false;
    }

    // Vai para o 5 byte do cabecalho (proxRRN) para pegar quantos registros existem
    fseek(p_bin, 5, SEEK_SET);
    int count_regs = 0;

    fread(&count_regs, sizeof(int), 1, p_bin);

    // Struct registro auxiliar para ler o binario
    REG registro;

    bool encontrou = false;

    // For que passa por todos os registros gravados no arquivo .bin
    for (int RRN = 0; RRN < count_regs; RRN++)
    {
        // Vai para o primeiro byteoffset do registro de RRN x
        fseek(p_bin, RRN * 80 + 17, SEEK_SET);

        read_from_bin(p_bin, &registro);

        // Verifica se o registro está removido , e se estiver não printa
        if (registro.removido == '0')
        {
            if (match_gabarito(&registro, pesquisa, &gabarito))
            {
                print_registro_in_terminal(&registro);
                encontrou = true;
            }
        }
    }

    if (count_regs == 0 || !encontrou)
    {
        printf("Registro inexistente.\n");
    }

    // Fecha os arquivos
    fclose(p_bin);
    p_bin = NULL;

    return true;
}
