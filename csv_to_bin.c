#include "IO.h"
#include "hash_tables.h"
#include "registro.h"
#include "sql_functions.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Função auxiliar para fechar os arquivos
void close_files(FILE *f_bin, FILE *f_csv)
{
    if (f_bin)
        fclose(f_bin);
    if (f_csv)
        fclose(f_csv);
}

// Função auxiliar para liberar a memória das hash tables
void free_tables(HashEstacao *hash_single, HashPar *hash_pair)
{
    if (hash_single)
        free_hash_estacao(hash_single);
    if (hash_pair)
        free_hash_par(hash_pair);
}

// Função principal para converter o arquivo .csv para .bin
void csv_to_bin()
{
    // Leitura dos nomes dos arquivos .csv e .bin
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
        free_tables(hash_single, hash_pair);
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Abertura do arquivo .csv para leitura
    FILE *f_csv = fopen(csv_name, "r");
    if (f_csv == NULL)
    {
        free_tables(hash_single, hash_pair);
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Criação do arquivo .bin com escrita binária
    FILE *f_bin = fopen(bin_name, "wb");
    if (f_bin == NULL)
    {
        free_tables(hash_single, hash_pair);
        fclose(f_csv);
        printf("Falha na criação do arquivo.\n");
        return;
    }

    // Escreve o status como inconsistente no início do arquivo binário
    char status = '0';
    fwrite(&status, sizeof(char), 1, f_bin);

    // Move o ponteiro de arquivo para o byte 17, logo após o registro de
    // cabeçalho
    fseek(f_bin, 17, SEEK_SET);

    char buffer[256];
    REG registro;
    int reg_count = 0;

    // Pula a linha de cabeçalho do arquivo .csv
    if (fgets(buffer, sizeof(buffer), f_csv) == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Lê o arquivo CSV linha por linha e processa cada registro escrevendo no
    // arquivo binário
    while (fgets(buffer, sizeof(buffer), f_csv) != NULL)
    {
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
        // inteiro E salva no registro auxiliar
        token = strsep(&p, ",");
        if (token == NULL)
        {
            free_tables(hash_single, hash_pair);
            fclose(f_csv);
            fclose(f_bin);
            printf("Falha no processamento do arquivo.");
            return;
        }
        registro.codEstacao = satoi(token, -1);

        // Processa o segundo token (nome da estação)
        // E salva o tamanho e a string no registro auxiliar
        token = strsep(&p, ",");
        if (token == NULL)
        {
            free_tables(hash_single, hash_pair);
            fclose(f_csv);
            fclose(f_bin);
            printf("Falha no processamento do arquivo.");
            return;
        }
        registro.tamNomeEstacao = strlen(token);
        strcpy(registro.nomeEstacao, token);

        // Transforma o terceiro token (código da linha) de string para inteiro
        // E salva no registro auxiliar
        token = strsep(&p, ",");
        if (token == NULL)
        {
            free_tables(hash_single, hash_pair);
            fclose(f_csv);
            fclose(f_bin);
            printf("Falha no processamento do arquivo.");
            return;
        }
        registro.codLinha = satoi(token, -1);

        // Processa o quarto token (nome da linha)
        // E salva o tamanho e a string no registro auxiliar
        token = strsep(&p, ",");
        if (token == NULL)
        {
            registro.tamNomeLinha = 0;
            registro.nomeLinha[0] = '\0';
        }
        else
        {
            registro.tamNomeLinha = strlen(token);
            strcpy(registro.nomeLinha, token);
        }

        // Transforma o quinto token (código da próxima estação) de string para
        // inteiro E salva no registro auxiliar
        token = strsep(&p, ",");
        if (token == NULL)
        {
            free_tables(hash_single, hash_pair);
            fclose(f_csv);
            fclose(f_bin);
            printf("Falha no processamento do arquivo.");
            return;
        }
        registro.codProxEstacao = satoi(token, -1);

        // Transforma o sexto token (distância para a próxima estação) de string
        // para inteiro E salva no registro auxiliar
        token = strsep(&p, ",");
        if (token == NULL)
        {
            free_tables(hash_single, hash_pair);
            fclose(f_csv);
            fclose(f_bin);
            printf("Falha no processamento do arquivo.");
            return;
        }
        registro.distProxEstacao = satoi(token, -1);

        // Transforma o sétimo token (código da linha de integração) de string
        // para inteiro E salva no registro auxiliar
        token = strsep(&p, ",");
        if (token == NULL)
        {
            free_tables(hash_single, hash_pair);
            fclose(f_csv);
            fclose(f_bin);
            printf("Falha no processamento do arquivo.");
            return;
        }
        registro.codLinhaIntegra = satoi(token, -1);

        // Transforma o oitavo token (código da estação de integração) de string
        // para inteiro E salva no registro auxiliar
        token = strsep(&p, ",");
        if (token == NULL)
        {
            free_tables(hash_single, hash_pair);
            fclose(f_csv);
            fclose(f_bin);
            printf("Falha no processamento do arquivo.");
            return;
        }
        // Limpa o último token, caso ainda tenha sobrado quebras de linha
        token[strcspn(token, "\r\n")] = '\0';
        registro.codEstIntegra = satoi(token, -1);

        // Escreve o registro no arquivo binário
        write_in_bin(f_bin, &registro);

        inserir_estacao(hash_single, registro.nomeEstacao);
        inserir_par(hash_pair, registro.codEstacao, registro.codProxEstacao);

        reg_count++;
    }

    // Escrita do registro de cabeçalho

    // Aponta para o topo da lista de removidos e escreve o valor -1, indicando
    // que não há registros removidos
    fseek(f_bin, 1, SEEK_SET);
    int topo = -1;
    fwrite(&topo, sizeof(int), 1, f_bin);

    // Escreve o próximo RRN
    fwrite(&reg_count, sizeof(int), 1, f_bin);

    // Escreve o número de estações únicas
    int nroEstacoes = get_nro_estacoes(hash_single);
    fwrite(&nroEstacoes, sizeof(int), 1, f_bin);

    // Escreve o número de pares únicos de estações
    int nroParesEstacao = get_nro_pares(hash_pair);
    fwrite(&nroParesEstacao, sizeof(int), 1, f_bin);

    // Aponta para o inicio do arquivo binário e escreve o status como
    // consistente pois o arquivo foi escrito com sucesso
    fseek(f_bin, 0, SEEK_SET);
    status = '1';
    fwrite(&status, sizeof(char), 1, f_bin);

    // Fecha os arquivos e desaloca as hashtables
    close_files(f_bin, f_csv);
    free_tables(hash_single, hash_pair);

    BinarioNaTela(bin_name);

    return;
}
