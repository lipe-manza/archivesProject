#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sql_functions.h"
#include "IO.h"
#include "filtro.h"

void select_from()
{
    char bin_name[41];

    if (scanf("%s", bin_name) != 1)
        return;
    FILE *p_bin = fopen(bin_name, "rb"); // Tenta criar .bin para escrita binaria
    if (p_bin == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    char status;
    if (fread(&status, sizeof(char), 1, p_bin) != 1)
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(p_bin);
        return;
    }
    if (status == '0')
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(p_bin);
        return;
    }

    // Vai para o 5 byte do cabecalho (proxRRN) para pegar quantos registros existem
    fseek(p_bin, 5, SEEK_SET);
    int count_regs = 0;

    if (fread(&count_regs, sizeof(int), 1, p_bin) != 1)
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(p_bin);
        return;
    }

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
            // print_registro_in_terminal(&registro);
            print_registro_in_terminal(&registro);
    }

    if (count_regs == 0)
    {
        printf("Registro inexistente.\n");
    }

    // Fecha os arquivos
    fclose(p_bin);
    p_bin = NULL;

    return;
}

void select_from_where()
{ // Lê o nome do arquivo binário
    char bin_name[41];
    scanf("%s", bin_name);

    FILE *p_bin = fopen(bin_name, "rb"); // Tenta criar .bin para escrita binaria
    if (p_bin == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    char status;
    fread(&status, sizeof(char), 1, p_bin);
    if (status == '0')
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(p_bin);
        return;
    }

    // Array auxiliar para informar quais campos devem ser pesquisados e comparados com o filtro
    int n;
    if (scanf("%d", &n) != 1)
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(p_bin);
        return;
    }

    for (int iter = 0; iter < n; iter++)
    {
        int m = 0;
        scanf(" %d", &m);

        // Array auxiliar para informar quais campos devem ser pesquisados e comparados com o filtro
        bool pesquisa[PUBLIC_FIELDS];
        for (int i = 0; i < PUBLIC_FIELDS; i++)
            pesquisa[i] = 0;

        // Struct registro auxiliar para ler o binario
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
                return;
            }

            // Seta como void a pesquisa do campo op
            pesquisa[op] = true;

            // Limpa a string
            str[0] = '\0';

            // Le o valor do campo a ser pesquisado e coloca no str
            ScanQuoteString(str);
            // Coloca no registro filtro o que os valores nos campos que vão ser buscados
            set_filtro(&filtro, op, str);
        }

        // Vai para o 5 byte do cabecalho (proxRRN) para pegar quantos registros existem
        fseek(p_bin, 5, SEEK_SET);
        int count_regs = 0;

        fread(&count_regs, sizeof(int), 1, p_bin);

        // Struct registro auxiliar para ler o binario
        REG registro;

        bool encontrou = false;

        // For que passa por todos os registros gravados no arquivo .bin
        for (int RRN = 0; RRN < count_regs; RRN++)
        {
            // Vai para o primeiro byteoffset do registro de RRN x
            fseek(p_bin, RRN * 80 + 17, SEEK_SET);

            read_from_bin(p_bin, &registro);

            // Verifica se o registro está removido , e se estiver não printa
            if (registro.removido == '0')
            {
                if (match_filtro(&registro, pesquisa, &filtro))
                {
                    print_registro_in_terminal(&registro);
                    encontrou = true;
                }
            }
        }

        if (count_regs == 0 || !encontrou)
        {
            printf("Registro inexistente.\n");
        }

        printf("\n");
    }

    // Fecha os arquivos
    fclose(p_bin);
    p_bin = NULL;
}
