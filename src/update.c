#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/sql_functions.h"
#include "../include/filtro.h"
#include "../include/IO.h"


bool update_set_where(char *bin_name)
{
    //BUSCA
    int m = 0;
    scanf(" %d", &m);

    // Array auxiliar para informar quais campos devem ser pesquisados e comparados com o atualizado
    bool buscar[PUBLIC_FIELDS];
    for (int i = 0; i < PUBLIC_FIELDS; i++)
        buscar[i] = 0;

    // Registro que guarda os valores de seleção fornecidos pelo usuário
    REG filtro;

    char str[41];

    for (int i = 0; i < m; i++)
    {
        // le o campo que quer em um buffer
        char field[41];
        scanf(" %s", field);
        // jogar esse buffer para o "hash" retorna op
        int op = field_to_index(field);

        if (op == -1)
        {
            printf("Campo não existente.\n");
            return false;
        }

        // Seta como true a atualizar do campo op
        buscar[op] = true;

        // Limpa a string
        str[0] = '\0';

        // Le o valor do campo a ser pesquisado e coloca no str
        ScanQuoteString(str);

        // Coloca no registro atualizado o que os valores nos campos que vão ser buscados
        set_filtro(&filtro, op, str);
    }

    // ATUALIZAÇÂO

    int p = 0;
    scanf(" %d", &p);

    // Registro que guarda os valores a serem atualizados
    REG atualizado;

    // Array auxiliar para informar quais campos devem ser pesquisados e comparados com o atualizado
    bool atualizar[PUBLIC_FIELDS];
    for (int i = 0; i < PUBLIC_FIELDS; i++)
        atualizar[i] = 0;

    for (int i = 0; i < m; i++)
    {
        // le o campo que quer em um buffer
        char field[41];
        scanf(" %s", field);
        // jogar esse buffer para o "hash" retorna op
        int op = field_to_index(field);

        if (op == -1)
        {
            printf("Campo não existente.\n");
            return false;
        }

        // Seta como true a atualizar do campo op
        atualizar[op] = true;

        // Limpa a string
        str[0] = '\0';

        // Le o valor do campo a ser atualizado e coloca no str
        ScanQuoteString(str);

        // Coloca no registro atualizado o que os valores nos campos que vão ser atualizado
        set_filtro(&atualizado, op, str);
    }

    // Abre o arquivo para leitura e escrita em modo binário
    FILE *p_bin = fopen(bin_name, "rb+");
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

    status = '0';
    fwrite(&status, sizeof(char), 1, p_bin);

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
        {
            if (match_filtro(&registro, buscar, &filtro))
            {
                atualizar_registro(&atualizado, atualizar, RRN, p_bin);
            }
        }
    }

    // Define o arquivo binário como consistente no registro de cabeçalho
    status = '1';
    fwrite(&status, sizeof(char), 1, p_bin);

    // Fecha os arquivos
    fclose(p_bin);
    p_bin = NULL;

    return true;
}
