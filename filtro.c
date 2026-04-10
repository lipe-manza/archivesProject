#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "filtro.h"

// Função auxiliar "hash" para converter o nome do campo em um inteiro representando o campo
int field_to_index(char *str)
{
    char *fields[] = {"codEstacao", "codLinha", "codProxEstacao", "distProxEstacao", "codLinhaIntegra", "codEstIntegra", "nomeEstacao", "nomeLinha"};

    for (int i = 0; i < PUBLIC_FIELDS; i++)
    {
        if (strcmp(str, fields[i]) == 0)
            return i;
    }

    // Se o campo não for encontrado retorna -1 para indicar que o campo é inválido
    return -1;
}

// Função para setar os campos do filtro de acordo com o campo a ser pesquisado e o valor lido do terminal
void set_filtro(REG *filtro, int op, char *str)
{
    switch (op)
    {
    case 0:
        filtro->codEstacao = (strlen(str) == 0) ? -1 : atoi(str);
        break;
    case 1:
        filtro->codLinha = (strlen(str) == 0) ? -1 : atoi(str);
        break;
    case 2:
        filtro->codProxEstacao = (strlen(str) == 0) ? -1 : atoi(str);
        break;
    case 3:
        filtro->distProxEstacao = (strlen(str) == 0) ? -1 : atoi(str);
        break;
    case 4:
        filtro->codLinhaIntegra = (strlen(str) == 0) ? -1 : atoi(str);
        break;
    case 5:
        filtro->codEstIntegra = (strlen(str) == 0) ? -1 : atoi(str);
        break;
    case 6:
        filtro->tamNomeEstacao = strlen(str);
        strcpy(filtro->nomeEstacao, str);
        break;
    case 7:
        filtro->tamNomeLinha = strlen(str);
        strcpy(filtro->nomeLinha, str);
        break;
    }
}

// Função para comparar um registro lido do arquivo binário com o filtro de pesquisa, retornando true se o registro corresponde ao filtro e false caso contrário
bool match_filtro(REG *reg, bool pesquisa[], REG *filtro)
{
    for (int i = 0; i < PUBLIC_FIELDS; i++)
    {
        if (!pesquisa[i])
            continue;

        switch (i)
        {
        case 0:
            if (reg->codEstacao != filtro->codEstacao)
                return false;
            break;
        case 1:
            if (reg->codLinha != filtro->codLinha)
                return false;
            break;
        case 2:
            if (reg->codProxEstacao != filtro->codProxEstacao)
                return false;
            break;
        case 3:
            if (reg->distProxEstacao != filtro->distProxEstacao)
                return false;
            break;
        case 4:
            if (reg->codLinhaIntegra != filtro->codLinhaIntegra)
                return false;
            break;
        case 5:
            if (reg->codEstIntegra != filtro->codEstIntegra)
                return false;
            break;
        case 6:
            if (strcmp(reg->nomeEstacao, filtro->nomeEstacao) != 0)
                return false;
            break;
        case 7:
            if (strcmp(reg->nomeLinha, filtro->nomeLinha) != 0)
                return false;
            break;
        }
    }

    return true;
}
