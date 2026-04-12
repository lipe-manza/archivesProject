#include "IO.h"
#include "filtro.h"
#include "sql_functions.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void select_from()
{
    char bin_name[50];

    // Lê o nome do arquivo binário
    if (scanf("%s", bin_name) != 1)
    {
        printf("Falha na leitura do nome do arquivo.\n");
        return;
    }

    // Abre o arquivo .bin para leitura e escrita e verifica se a abertura
    // foi bem sucedida conferindo o status do arquivo
    FILE *f_bin = open_bin(bin_name, "rb+");

    if (f_bin == NULL)
        return;

    // Vai para o campo proxRRN do registro de cabeçalho para ler quantos
    // registros existem
    int reg_count = 0;
    fseek(f_bin, 5, SEEK_SET);
    if (fread(&reg_count, sizeof(int), 1, f_bin) != 1)
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(f_bin);
        return;
    }

    // Struct registro auxiliar para ler o .bin
    REG registro;

    // Flag para indicar se algum registro foi encontrado
    bool encontrou = false;

    // Itera pelos registros do .bin
    for (int RRN = 0; RRN < reg_count; RRN++)
    {
        // Vai para o byteoffset do registro atual
        fseek(f_bin, RRN * 80 + 17, SEEK_SET);

        // Lê o registro do .bin para a struct registro
        read_from_bin(f_bin, &registro);

        // O registro só é impresso se não estiver removido
        if (registro.removido == '0')
        {
            encontrou = true;
            print_registro_in_terminal(&registro);
        }
    }

    // Se nenhum registro foi encontrado, o usuário é avisado
    if (!encontrou)
    {
        printf("Registro inexistente.\n");
    }

    // Fecha o arquivo .bin
    fclose(f_bin);
    f_bin = NULL;
}

void select_from_where()
{
    char bin_name[50];
    // Lê o nome do arquivo binário
    if (scanf("%s", bin_name) != 1)
    {
        printf("Falha na leitura do nome do arquivo.\n");
        return;
    }

    // Abre o arquivo .bin para leitura e escrita e verifica se a abertura
    // foi bem sucedida conferindo o status do arquivo
    FILE *f_bin = open_bin(bin_name, "rb+");
    if (f_bin == NULL)
        return;

    // Vai para o campo proxRRN do registro de cabeçalho para ler quantos
    // registros existem
    int reg_count = 0;
    fseek(f_bin, 5, SEEK_SET);
    if (fread(&reg_count, sizeof(int), 1, f_bin) != 1)
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(f_bin);
        return;
    }

    // Lê o número de consultas a serem feitas
    int n;
    if (scanf("%d", &n) != 1)
    {
        printf("Entrada inválida.\n");
        fclose(f_bin);
        return;
    }

    // Itera sobre as consultas
    for (int i = 0; i < n; i++)
    {
        // Struct registro que serve como comparação para filtrar
        // os registros do arquivo .bin
        REG filter;

        // Flag para indicar se algum registro foi encontrado
        bool encontrou = false;

        // Array auxiliar para informar quais campos devem ser pesquisados e
        // comparados com o filtro
        bool search[PUBLIC_FIELDS];

        // Preenche a struct filter e o array search com os valores do filtro de pesquisa
        filter_build(&filter, search);

        // Struct registro auxiliar para ler o .bin
        REG registro;

        // Itera pelos registros do .bin
        for (int RRN = 0; RRN < reg_count; RRN++)
        {
            // Vai para o byteoffset do registro atual
            fseek(f_bin, RRN * 80 + 17, SEEK_SET);

            // Lê o registro do .bin para a struct registro
            read_from_bin(f_bin, &registro);

            // Se o registro está removido ele não é selecionado
            if (registro.removido == '1')
                continue;

            // Se o registro passa pelo filtro ele é impresso
            if (match_filter(&registro, search, &filter))
            {
                encontrou = true;
                print_registro_in_terminal(&registro);
            }
        }

        // Se nenhum registro foi encontrado, o usuário é avisado
        if (!encontrou)
        {
            printf("Registro inexistente.\n");
        }

        // Separa as consultas por uma linha em branco
        printf("\n");
    }

    // Fecha o arquivo .bin
    fclose(f_bin);
    f_bin = NULL;
}
