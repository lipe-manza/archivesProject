#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../include/registro.h"


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

            // Atualiza os campos do nome da linha
            fseek(p_bin, RRN * 80 + 17 + 33 + tamNomeEstacao, SEEK_SET);
            if (atualizado->tamNomeLinha > 0)
                fwrite(atualizado->nomeLinha, sizeof(char), atualizado->tamNomeLinha, p_bin);

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
