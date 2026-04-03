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

void free_tables(HASH_S *hash_single, HASH_P *hash_pair)
{
    if (hash_single)
        hash_table_single_free(&hash_single);
    if (hash_pair)
        hash_table_pair_free(&hash_pair);
}


bool csv_to_bin(char *csv_name, char *bin_name)
{
    // Cria as hashtables para contar as estações e pares de estaçõs únicas
    HASH_S *hash_single = hash_table_single();
    HASH_P *hash_pair = hash_table_pair();

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
    REG reg ;
    int count_regs = 0;

    // Pula a primeira linha
    fgets(buffer, sizeof(buffer), p_csv);

    while (fgets(buffer, sizeof(buffer), p_csv) != NULL)
    {
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
        strcpy(reg.nomeEstacao, token); // pode ser so /0 ai lidar com isso

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
        reg.tamNomeLinha = strlen(token);
        strcpy(reg.nomeLinha, token);

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


        // Insere a estação na hash table para contar quantas existem
        hash_table_single_insert(hash_single, reg.codEstacao);
        // Insere as estação na hash table para contar quantos pares existem
        hash_table_pair_insert(hash_pair, reg.codEstacao, reg.codProxEstacao);
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
    int nroEstacoes = hash_table_single_get_count(hash_single);
    fwrite(&nroEstacoes, sizeof(int), 1, p_bin);

    // Escreve o número de pares únicos de estações
    int nroParesEstacao = hash_table_pair_get_count(hash_pair);
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
