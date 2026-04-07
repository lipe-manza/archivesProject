#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/sql_functions.h"
#include "../include/hash_tables.h"
#include "../include/IO.h"

/*
typedef struct cabecalho
{
    char status; // 0 inconsistente 1 consistente
    int topo;
    int proxRRN; // n de registros - 1; byteoffset = 17 + (RRN * 80)
    int nroEstacoes;
    int nroParesEstacoes;
} CAB;
*/

void close_files(FILE *p_bin, FILE *p_csv)
{
    if (p_bin)
        fclose(p_bin);
    if (p_csv)
        fclose(p_csv);
}

void free_tables(HashEstacao *hash_single, HashPar *hash_pair)
{
    if (hash_single)
        destruir_hash_est(hash_single);
    if (hash_pair)
        destruir_hash_par(hash_pair);
}

bool csv_to_bin(char *csv_name, char *bin_name)
{
    // Cria as hashtables para contar as estações e pares de estaçõs únicas
    HashEstacao *hash_single = criar_hash_est();
    HashPar *hash_pair = criar_hash_par();

    // Encerra o programa em caso de falha de alocação de algum dos if (hash_single == NULL || hash_pair == NULL)
    if (hash_single == NULL || hash_pair == NULL)
    {
        free(hash_single);
        free(hash_pair);
        printf("Falha no processamento do arquivo\n");
        printf("Hash\n");
        return false;
    }

    // Tenta abrir o arquivo cvs para leitura
    FILE *p_csv = fopen(csv_name, "r");
    if (p_csv == NULL)
    {
        free(hash_single);
        free(hash_pair);
        printf("Falha no processamento do arquivo\n");
        printf("fopen csv\n");
        return false;
    }

    FILE *p_bin = fopen(bin_name, "wb"); // Tenta criar .bin para escrita binaria
    if (p_bin == NULL)
    {
        printf("Falha no processamento do arquivo\n");
        printf("fopen bin\n");
        return false;
    }

    char status = '0';
    fwrite(&status, sizeof(char), 1, p_bin); // Status inconsistente

    // pula 17 bytes para depois ser preenchido pelo cabecalho
    fseek(p_bin, 17, SEEK_SET);

    // variaveis de ajuda
    char buffer[256];
    REG reg;
    int count_regs = 0;

    // Pula a primeira linha
    fgets(buffer, sizeof(buffer), p_csv);

    while (fgets(buffer, sizeof(buffer), p_csv) != NULL)
    {
        buffer[strcspn(buffer, "\r\n")] = '\0';

        char *p = buffer;
        char *token;

        // Inicializa removido e proximo
        reg.removido = '0';
        reg.proximo = -1;

        // pega o primeiro campo do csv (CodEstacao) e transforma o numero lido de string para int
        token = strsep(&p, ",");
        if (token == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return false;
        }
        reg.codEstacao = atoi(token);

        // pega o segundo campo do csv (NomeEstacao) string
        token = strsep(&p, ",");
        if (token == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return false;
        }
        reg.tamNomeEstacao = strlen(token);
        strcpy(reg.nomeEstacao, token);

        // CodLinha
        token = strsep(&p, ",");
        if (token == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return false;
        }
        reg.codLinha = (strlen(token) > 0) ? atoi(token) : -1;

        // NomeLinha
        token = strsep(&p, ",");
        if (token == NULL)
        {
            reg.tamNomeLinha = 0;
            reg.nomeLinha[0] = '\0';
        }
        else
        {
            reg.tamNomeLinha = strlen(token);
            strcpy(reg.nomeLinha, token);
        }

        // CodProxEst
        token = strsep(&p, ",");
        if (token == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return false;
        }
        reg.codProxEstacao = (strlen(token) > 0) ? atoi(token) : -1;

        // DistanciaProxEst
        token = strsep(&p, ",");
        if (token == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return false;
        }
        reg.distProxEstacao = (strlen(token) > 0) ? atoi(token) : -1;

        // CodLinhaInteg
        token = strsep(&p, ",");
        if (token == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return false;
        }
        reg.codLinhaIntegra = (strlen(token) > 0) ? atoi(token) : -1;

        // CodEstacaoInteg
        token = strsep(&p, ",");
        if (token == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return false;
        }
        // Trunca a ultima string se for vazia tirando o \r e o \n
        token[strcspn(token, "\r\n")] = '\0';
        reg.codEstIntegra = (strlen(token) > 0) ? atoi(token) : -1;

        // Escreve o registro no binário
        write_in_bin(p_bin, &reg);

        char str_nomeEstacao[41];
        strcpy(str_nomeEstacao, reg.nomeEstacao);
        int codEstacao = reg.codEstacao;
        int codProxEstacao = reg.codProxEstacao;

        // Insere a estação na hash table para contar quantas existem
        inserir_est(hash_single, str_nomeEstacao);
        // Insere as estação na hash table para contar quantos pares existem
        inserir_par(hash_pair, codEstacao, codProxEstacao);
        // conta quantos registros para o RRN
        count_regs++;
    }

    // REGISTRO DE CABECALHO
    // Aponta para o topo
    fseek(p_bin, 1, SEEK_SET);

    // Escreve o topo
    int topo = -1;
    fwrite(&topo, sizeof(int), 1, p_bin);

    // Escreve o próximo RRN
    fwrite(&count_regs, sizeof(int), 1, p_bin);

    // Escreve o número de estações únicas
    int nroEstacoes = get_nro_estacoes(hash_single);
    fwrite(&nroEstacoes, sizeof(int), 1, p_bin);

    // Escreve o número de pares únicos de estações
    int nroParesEstacao = get_nro_pares(hash_pair);
    fwrite(&nroParesEstacao, sizeof(int), 1, p_bin);

    // Aponta para o inicio do arquivo
    fseek(p_bin, 0, SEEK_SET);

    // Define status como consistente
    status = '1';
    fwrite(&status, sizeof(char), 1, p_bin);

    // Fecha os arquivos e da free nos hashs
    close_files(p_bin, p_csv);

    // Desaloca a memória das hash tables
    free_tables(hash_single, hash_pair);

    return true;
}
