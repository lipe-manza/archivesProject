#include "filtro.h"
#include "IO.h"
#include <stdbool.h>
#include <string.h>

// Função auxiliar "hash" para converter o nome do campo em um inteiro
// representando o campo
int field_to_index(char *str)
{
    char *fields[] = {"codEstacao",      "codLinha",        "codProxEstacao",
                      "distProxEstacao", "codLinhaIntegra", "codEstIntegra",
                      "nomeEstacao",     "nomeLinha"};

    for (int i = 0; i < PUBLIC_FIELDS; i++)
    {
        if (strcmp(str, fields[i]) == 0)
            return i;
    }

    // Se o campo não for encontrado retorna -1 para indicar que o campo é
    // inválido
    return -1;
}

// Função para setar os campos do filtro de acordo com o campo a ser pesquisado
// e o valor lido do terminal
void set_filter_field(REG *filter, int field, char *field_val)
{
    switch (field)
    {
    case 0:
        filter->codEstacao = satoi(field_val, -1);
        break;
    case 1:
        filter->codLinha = satoi(field_val, -1);
        break;
    case 2:
        filter->codProxEstacao = satoi(field_val, -1);
        break;
    case 3:
        filter->distProxEstacao = satoi(field_val, -1);
        break;
    case 4:
        filter->codLinhaIntegra = satoi(field_val, -1);
        break;
    case 5:
        filter->codEstIntegra = satoi(field_val, -1);
        break;
    case 6:
        filter->tamNomeEstacao = strlen(field_val);
        strcpy(filter->nomeEstacao, field_val);
        break;
    case 7:
        filter->tamNomeLinha = strlen(field_val);
        strcpy(filter->nomeLinha, field_val);
        break;
    }
}

void filter_build(REG *filter, bool search[])
{
    // Lê o número de campos a serem pesquisados
    int m = 0;
    scanf(" %d", &m);

    // Inicializa todas as posições como falso
    memset(search, false, PUBLIC_FIELDS * sizeof(bool));

    for (int j = 0; j < m; j++)
    {
        // Lê o campo a ser pesquisado e coloca em um buffer
        char field[41];
        if (scanf(" %s", field) != 1)
        {
            printf("Falha na leitura do campo.\n");
            return;
        }

        // Guarda um índice referente ao campo atual
        int field_idx = field_to_index(field);

        // Verifica se o campo lido é válido
        if (field_idx == -1)
        {
            printf("Campo não existente.\n");
            return;
        }

        // Marca que o campo fornecido será usado na pesquisa
        search[field_idx] = true;

        // String auxiliar para ler o valor do campo a ser pesquisado
        char field_val[41];

        // Limpa o buffer
        memset(field_val, '\0', sizeof(field_val));

        // Lê o valor do campo a ser pesquisado e coloca no buffer
        ScanQuoteString(field_val);

        // Coloca no registro filtro os valores lidos para comparar com os
        // registros do arquivo binário depois
        set_filter_field(filter, field_idx, field_val);
    }
}

// Função para comparar um registro lido do arquivo binário com o filtro de
// pesquisa, retornando true se o registro corresponde ao filtro e false caso
// contrário
bool match_filter(REG *reg, bool pesquisa[], REG *filtro)
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
