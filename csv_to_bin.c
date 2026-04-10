#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sql_functions.h"
#include "hash_tables.h"
#include "IO.h"

// Função  auxiliar para fechar os arquivos
void close_files(FILE *p_bin, FILE *p_csv)
{
    if (p_bin)
        fclose(p_bin);
    if (p_csv)
        fclose(p_csv);
}

// Função auxiliar para liberar a memória das hash tables
void free_tables(HashEstacao *hash_single, HashPar *hash_pair)
{
    if (hash_single)
        free_hash_estacao(hash_single);
    if (hash_pair)
        free_hash_par(hash_pair);
}

// Função principal para converter o arquivo CSV para BIN
void csv_to_bin()
{
    // Litura dos nomes dos arquivos .csv e .bin
    char bin_name[50];
    char csv_name[50];
    if (scanf("%s %s", csv_name, bin_name) != 2)
        return;

    // Cria as hashtables para contar as estações e pares de estaçõs únicas
    HashEstacao *hash_single = criar_hash_estacao();
    HashPar *hash_pair = criar_hash_par();

    // Encerra o programa em caso de falha de alocação de alguma das hashtables
    if (hash_single == NULL || hash_pair == NULL)
    {
        free(hash_single);
        free(hash_pair);
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Tenta abrir o arquivo cvs para leitura e verifica se ele foi aberto com sucesso
    FILE *p_csv = fopen(csv_name, "r");
    if (p_csv == NULL)
    {
        free(hash_single);
        free(hash_pair);
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Tenta criar o arquivo binário para escrita e verifica se ele foi criado com sucesso
    FILE *p_bin = fopen(bin_name, "wb");
    if (p_bin == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Escreve o status como inconsistente no início do arquivo binário
    char status = '0';
    fwrite(&status, sizeof(char), 1, p_bin);

    // pula 17 bytes para depois ser preenchido pelo cabecalho
    fseek(p_bin, 17, SEEK_SET);

    // variaveis de ajuda
    char buffer[256];
    REG reg;
    int count_regs = 0;

    // Lê o arquivo CSV linha por linha e processa cada registro escrevendo no arquivo binário
    while (fgets(buffer, sizeof(buffer), p_csv) != NULL)
    {
        // Trunca a linha lida para remover o \r e o \n
        buffer[strcspn(buffer, "\r\n")] = '\0';

        // Variáveis para tokenização da linha lida
        char *p = buffer;
        char *token;

        // Inicializa removido e proximo
        reg.removido = '0';
        reg.proximo = -1;

        // Tokeniza a linha lida usando strsep e separa os campos usando a vírgula como delimitador

        // Pega o primeiro campo do csv (CodEstacao) e transforma o numero lido de string para int sem verificar se ele é nulo, pois o campo não pode ser nulo
        token = strsep(&p, ",");
        if (token == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return;
        }
        reg.codEstacao = atoi(token);

        // Verifica se o primeiro campo é um número se não pula
        // Para pular a linha de cabeçalho do csv
        int t;
        if (sscanf(token, "%d", &t) != 1)
        {
            continue;
        }

        // Pega o segundo campo do csv (NomeEstacao) string sem verificar se ele é nulo, pois o campo não pode ser nulo
        token = strsep(&p, ",");
        if (token == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return;
        }
        reg.tamNomeEstacao = strlen(token);
        strcpy(reg.nomeEstacao, token);

        // Pega o terceiro campo do csv (CodLinha) e transforma o numero lido de string para int
        token = strsep(&p, ",");
        if (token == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return;
        }
        reg.codLinha = (strlen(token) > 0) ? atoi(token) : -1;

        // Pega o quarto campo do csv (NomeLinha) string
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

        // Pega o quinto campo do csv (CodProxEst) e transforma o numero lido de string para int
        token = strsep(&p, ",");
        if (token == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return;
        }
        reg.codProxEstacao = (strlen(token) > 0) ? atoi(token) : -1;

        // Pega o sexto campo do csv (DistanciaProxEst) e transforma o numero lido de string para int
        token = strsep(&p, ",");
        if (token == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return;
        }
        reg.distProxEstacao = (strlen(token) > 0) ? atoi(token) : -1;

        // Pega o sétimo campo do csv (CodLinhaInteg) e transforma o numero lido de string para int
        token = strsep(&p, ",");
        if (token == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return;
        }
        reg.codLinhaIntegra = (strlen(token) > 0) ? atoi(token) : -1;

        // Pega o oitavo campo do csv (CodEstacaoInteg) e transforma o numero lido de string para int
        token = strsep(&p, ",");
        if (token == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return;
        }
        // Trunca a ultima string se for vazia tirando o \r e o \n, apenas como precaução, pois no inicio do loop já é feita a truncagem da linha lida
        token[strcspn(token, "\r\n")] = '\0';
        reg.codEstIntegra = (strlen(token) > 0) ? atoi(token) : -1;

        // Escreve o registro no binário
        write_in_bin(p_bin, &reg);

        // Variáveis para inserir na hash tables
        char str_nomeEstacao[41];
        strcpy(str_nomeEstacao, reg.nomeEstacao);
        int codEstacao = reg.codEstacao;
        int codProxEstacao = reg.codProxEstacao;

        // Insere a estação na hash table para contar quantas existem
        inserir_estacao(hash_single, str_nomeEstacao);
        // Insere as estação na hash table para contar quantos pares existem
        inserir_par(hash_pair, codEstacao, codProxEstacao);
        // conta quantos registros para o RRN
        count_regs++;
    }

    // REGISTRO DE CABECALHO

    // Aponta para o topo da lista de removidos e escreve o valor -1, indicando que não há registros removidos
    fseek(p_bin, 1, SEEK_SET);
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

    // Aponta para o inicio do arquivo binário e escreve o status como consistente pois o arquivo foi escrito com sucesso
    fseek(p_bin, 0, SEEK_SET);
    status = '1';
    fwrite(&status, sizeof(char), 1, p_bin);

    // Fecha os arquivos e da free nos hashs
    close_files(p_bin, p_csv);
    free_tables(hash_single, hash_pair);

    // Chama a função binarioNaTela
    BinarioNaTela(bin_name);

    return;
}
