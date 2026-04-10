#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "registro.h"
#include "hash_tables.h"

void read_from_bin(FILE *p_bin, REG *reg)
{
    if (fread(&reg->removido, sizeof(reg->removido), 1, p_bin) != 1) return;
    if (fread(&reg->proximo, sizeof(reg->proximo), 1, p_bin) != 1) return;
    if (fread(&reg->codEstacao, sizeof(reg->codEstacao), 1, p_bin) != 1) return;
    if (fread(&reg->codLinha, sizeof(reg->codLinha), 1, p_bin) != 1) return;
    if (fread(&reg->codProxEstacao, sizeof(reg->codProxEstacao), 1, p_bin) != 1) return;
    if (fread(&reg->distProxEstacao, sizeof(reg->distProxEstacao), 1, p_bin) != 1) return;
    if (fread(&reg->codLinhaIntegra, sizeof(reg->codLinhaIntegra), 1, p_bin) != 1) return;
    if (fread(&reg->codEstIntegra, sizeof(reg->codEstIntegra), 1, p_bin) != 1) return;

    if (fread(&reg->tamNomeEstacao, sizeof(reg->tamNomeEstacao), 1, p_bin) != 1) return;
    if (reg->tamNomeEstacao > 0)
    {
        if (fread(reg->nomeEstacao, sizeof(char), reg->tamNomeEstacao, p_bin) != (size_t)reg->tamNomeEstacao) return;
        reg->nomeEstacao[reg->tamNomeEstacao] = '\0'; // coloca \0 na string
    }
    else
        reg->nomeEstacao[0] = '\0';

    if (fread(&reg->tamNomeLinha, sizeof(reg->tamNomeLinha), 1, p_bin) != 1) return;
    if (reg->tamNomeLinha > 0)
    {
        if (fread(reg->nomeLinha, sizeof(char), reg->tamNomeLinha, p_bin) != (size_t)reg->tamNomeLinha) return;
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

    // Escreve os bytes de lixo no final do registro para completar os 80 bytes do registro
    char lixo = '$';
    int bytes_usados = 37 + reg->tamNomeEstacao + reg->tamNomeLinha;
    int lixo_size = 80 - bytes_usados;

    for (int i = 0; i < lixo_size; i++)
    {
        fwrite(&lixo, sizeof(char), 1, p_bin);
    }
}

void atualizar_registro(REG *atualizado, bool atualizar[], int RRN, FILE *p_bin)
{

    for (int i = 0; i < 8; i++)
    {
        if (!atualizar[i])
            continue;

        switch (i)
        {
        case 0:
            fseek(p_bin, RRN * 80 + 17 + 5, SEEK_SET);
            fwrite(&atualizado->codEstacao, sizeof(atualizado->codEstacao), 1, p_bin);
            break;

        case 1:
            fseek(p_bin, RRN * 80 + 17 + 9, SEEK_SET);
            fwrite(&atualizado->codLinha, sizeof(atualizado->codLinha), 1, p_bin);
            break;

        case 2:
            fseek(p_bin, RRN * 80 + 17 + 13, SEEK_SET);
            fwrite(&atualizado->codProxEstacao, sizeof(atualizado->codProxEstacao), 1, p_bin);
            break;

        case 3:
            fseek(p_bin, RRN * 80 + 17 + 17, SEEK_SET);
            fwrite(&atualizado->distProxEstacao, sizeof(atualizado->distProxEstacao), 1, p_bin);
            break;

        case 4:
            fseek(p_bin, RRN * 80 + 17 + 21, SEEK_SET);
            fwrite(&atualizado->codLinhaIntegra, sizeof(atualizado->codLinhaIntegra), 1, p_bin);
            break;

        case 5:
            fseek(p_bin, RRN * 80 + 17 + 25, SEEK_SET);
            fwrite(&atualizado->codEstIntegra, sizeof(atualizado->codEstIntegra), 1, p_bin);
            break;

        case 6:
        {
            // Lê o tamanho do nome da estação para pegar o byteoffset do tamNomeLinha
            int antigo_tamNomeEstacao = 0;
            fseek(p_bin, RRN * 80 + 17 + 29, SEEK_SET);
            fread(&antigo_tamNomeEstacao, sizeof(int), 1, p_bin);

            // Pega o byteoffset do tamNomeLinha e guarda a string nomeEstacao usando esse byteoffset
            int tamNomeLinha = 0;
            char nomeLinha[41];
            fseek(p_bin, RRN * 80 + 17 + 33 + antigo_tamNomeEstacao, SEEK_SET);
            fread(&tamNomeLinha, sizeof(int), 1, p_bin);
            fread(nomeLinha, sizeof(char), tamNomeLinha, p_bin);

            // Escreve a string nova do atualizado no bin
            fseek(p_bin, RRN * 80 + 17 + 29, SEEK_SET);
            fwrite(&atualizado->tamNomeEstacao, sizeof(int), 1, p_bin);
            if (atualizado->tamNomeEstacao > 0)
                fwrite(atualizado->nomeEstacao, sizeof(char), atualizado->tamNomeEstacao, p_bin);

            // Atualiza os campos do nome da linha se foi requisitado
            if (atualizar[7])
            {
                fwrite(&atualizado->tamNomeLinha, sizeof(int), 1, p_bin);
                if (atualizado->tamNomeLinha > 0)
                    fwrite(atualizado->nomeLinha, sizeof(char), atualizado->tamNomeLinha, p_bin);
            }
            // Reescreve os campos do nome da linha no local correto
            else
            {
                fwrite(&tamNomeLinha, sizeof(int), 1, p_bin);
                if (tamNomeLinha > 0)
                    fwrite(nomeLinha, sizeof(char), atualizado->tamNomeLinha, p_bin);
            }

            // Escreve os bytes de lixo no final do registro
            char lixo = '$';

            int bytes_usados = 37 + atualizado->tamNomeEstacao;

            // Calcula a quantidade de bytes usados de acordo com a atualização (ou não) do nome da linha e caso o nome da linha já estiver sendo atualizado, impede que seja novamente
            if (atualizar[7])
            {
                bytes_usados += atualizado->tamNomeLinha;
                atualizar[7] = false;
            }
            else
                bytes_usados += tamNomeLinha;

            int lixo_size = 80 - bytes_usados;

            for (int i = 0; i < lixo_size; i++)
            {
                fwrite(&lixo, sizeof(char), 1, p_bin);
            }

            break;
        }
        case 7:
        {
            // Lê o tamanho do tamanho nome estação para saber onde atualizar os campos do nome da linha
            int tamNomeEstacao = 0;
            fseek(p_bin, RRN * 80 + 17 + 29, SEEK_SET);
            fread(&tamNomeEstacao, sizeof(int), 1, p_bin);

            fseek(p_bin, RRN * 80 + 17 + 33 + tamNomeEstacao, SEEK_SET);
            fwrite(&atualizado->tamNomeLinha, sizeof(int), 1, p_bin);
            if (atualizado->tamNomeLinha > 0)
                fwrite(atualizado->nomeLinha, sizeof(char), atualizado->tamNomeLinha, p_bin);

            // Escreve os bytes de lixo no final do registro
            char lixo = '$';
            int bytes_usados = 37 + tamNomeEstacao + atualizado->tamNomeLinha;
            int lixo_size = 80 - bytes_usados;

            for (int i = 0; i < lixo_size; i++)
            {
                fwrite(&lixo, sizeof(char), 1, p_bin);
            }
            break;
        }
        }
    }
}

bool atualizar_estacoes(FILE *p_bin)
{
    // Cria as hashtables para contar as estações e pares de estaçõs únicas
    HashEstacao *hash_single = criar_hash_estacao();
    HashPar *hash_pair = criar_hash_par();

    // Encerra o programa em caso de falha de alocação de algum dos if (hash_single == NULL || hash_pair == NULL)
    if (hash_single == NULL || hash_pair == NULL)
    {
        free(hash_single);
        free(hash_pair);
        printf("Falha no processamento do arquivo\n");
        return false;
    }

    // Aponta para o proxRRN
    fseek(p_bin, 5, SEEK_SET);
    int RRN;
    // Le o valor do proximo RRN
    fread(&RRN, sizeof(int), 1, p_bin);

    // Loop para ler o arquivo binário inteiro e atualizar na hash o numero de estacoes e pares de estacoes
    for (int i = 0; i < RRN; i++)
    {
        char removido = '0';
        fseek(p_bin, i * 80 + 17, SEEK_SET);
        fread(&removido, sizeof(char), 1, p_bin);

        if (removido == '1')
            continue;

        int tamNomeEstacao = 0;
        // Aponta para o tamNomeEstacao
        fseek(p_bin, i * 80 + 17 + 29, SEEK_SET);
        // Le o tamNomeEstacao e armazena
        fread(&tamNomeEstacao, sizeof(int), 1, p_bin);

        // Como o nomeEstacao nunca é nulo não precisa de verificação
        char nomeEstacao[41];
        fread(nomeEstacao, sizeof(char), tamNomeEstacao, p_bin);
        nomeEstacao[tamNomeEstacao] = '\0'; // coloca \0 na string
        inserir_estacao(hash_single, nomeEstacao);

        int codEstacao = -1;
        // Aponta para o codEstacao
        fseek(p_bin, i * 80 + 17 + 5, SEEK_SET);
        // Le o codEstacao e armazena
        fread(&codEstacao, sizeof(int), 1, p_bin);

        int codProxEstacao = -1;
        // Aponta para o codProxEstacao
        fseek(p_bin, i * 80 + 17 + 13, SEEK_SET);
        // Le o codProxEstacao e armazena
        fread(&codProxEstacao, sizeof(int), 1, p_bin);
        // Insere a dupla na hash_table_pair
        inserir_par(hash_pair, codEstacao, codProxEstacao);
    }

    // Variaveis para armazenar o numero de estações e pares de estações únicas
    int nroEstacoes = get_nro_estacoes(hash_single);
    int nroParesEstacao = get_nro_pares(hash_pair);

    // Aponta para nroEstacoes
    fseek(p_bin, 9, SEEK_SET);
    // Escreve no arquivo o numero de estacoes e o numero de pares de estacoes
    fwrite(&nroEstacoes, sizeof(int), 1, p_bin);
    fwrite(&nroParesEstacao, sizeof(int), 1, p_bin);

    // Dar free nas hashtables
    free_hash_estacao(hash_single);
    free_hash_par(hash_pair);

    return true;
}
