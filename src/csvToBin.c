#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct reg
{
    bool removido;
    int proximo;
    int codEstacao;
    int codLinha;
    int codProxEstacao;
    int distProxEstacao;
    int codLinhaIntegra;
    int codEstIntegra;
    int tamNomeEstacao; // se for 0 nao escrever o nomeestacao
    char nomeEstacao[41];
    int tamNomeLinha;
    char nomeLinha[41];
} REG;

void write_in_bin(FILE *p_bin, REG *reg)
{
    long start = ftell(p_bin);

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

    long cur = ftell(p_bin);

    long end = start + 80;
    char lixo = '$';
    while (cur != end)
    {
        fwrite(&lixo, sizeof(lixo), 1, p_bin);
        cur++;
    }
}

FILE *csv_to_bin(char *csv_name, char *bin_name)

{
    // Cria a string de caminho onde será aberto o arquivo.csv
    char csv_path[50];
    strcpy(csv_path, "data/");
    strcat(csv_path, csv_name);

    // Tenta abrir o arquivo cvs para leitura
    FILE *p_csv = fopen(csv_path, "r");
    if (p_csv == NULL)
    {
        printf("Falha no processamento do arquivo\n");
        return NULL;
    }
    // ! Definir o registro de cabecalho como instavel

    // Cria a string de caminho onde será aberto ou criado o arquivo.bin
    char bin_path[50];
    strcpy(bin_path, "bin/");
    strcat(bin_path, bin_name);

    FILE *p_bin = fopen(bin_path, "wb"); // Tenta criar .bin para escrita binaria
    if (p_bin == NULL)
    {
        printf("Falha no processamento do arquivo\n");
        return NULL;
    }
    fseek(p_bin, 17, SEEK_SET); // pula 17 bytes para depois ser preenchido pelo cabecalho

    // variaveis de ajuda
    char buffer[256];
    REG reg;
    int count_regs = 0;

    // Pula a primeira linha
    fgets(buffer, sizeof(buffer), p_csv);

    while (fgets(buffer, sizeof(buffer), p_csv) != NULL)
    {
        char *p = buffer;
        char *token;

        // Inicializa removido e proximo
        reg.removido = false;
        reg.proximo = -1;

        // pega o primeiro campo do csv (CodEstacao) e transforma o numero lido de string para int
        token = strsep(&p, ",");
        if (token == NULL)
            // BO
            return NULL;
        reg.codEstacao = atoi(token);

        // pega o segundo campo do csv (NomeEstacao) string
        token = strsep(&p, ",");
        reg.tamNomeEstacao = strlen(token);
        strcpy(reg.nomeEstacao, token); // pode ser so /0 ai lidar com isso

        // CodLinha
        token = strsep(&p, ",");
        reg.codLinha = atoi(token);

        // NomeLinha
        token = strsep(&p, ",");
        reg.tamNomeLinha = strlen(token);
        strcpy(reg.nomeLinha, token);

        // CodProxEst
        token = strsep(&p, ",");
        reg.codProxEstacao = atoi(token);

        // DistanciaProxEst
        token = strsep(&p, ",");
        reg.distProxEstacao = atoi(token);

        // CodLinhaInteg
        token = strsep(&p, ",");
        reg.codLinhaIntegra = atoi(token);

        // CodEstacaoInteg
        token = strsep(&p, ",");
        reg.codEstIntegra = atoi(token);

        // ? hash para definir nro estacoes e nro pares estacao
        //
        write_in_bin(p_bin, &reg);

        count_regs++;
        // Pular 16 bytes para o registro de cabecalho e depois voltar para preencher
    }

    // free()
}
