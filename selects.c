#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sql_functions.h"
#include "IO.h"
#include "filtro.h"

void select_from()
{
    // Lê o nome do arquivo binário
    char bin_name[41];
    if (scanf("%s", bin_name) != 1)
        return;

    // Tenta abrir o arquivo binário para leitura
    FILE *p_bin = fopen(bin_name, "rb");
    if (p_bin == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Verifica se o status do arquivo é consistente ou seja, se é '1'
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

        // Lê o registro do arquivo binário para a struct registro
        read_from_bin(p_bin, &registro);

        // Verifica se o registro está removido , e se estiver não printa
        if (registro.removido == '0')
            // print_registro_in_terminal(&registro);
            print_registro_in_terminal(&registro);
    }

    // Caso não haja registros para serem lidos, ou seja, o proxRRN for 0, printa que o registro é inexistente
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
{
    // Lê o nome do arquivo binário
    char bin_name[41];
    if (scanf("%s", bin_name) != 1)
        return;

    // Tenta abrir o arquivo binário para leitura
    FILE *p_bin = fopen(bin_name, "rb");
    if (p_bin == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Verifica se o status do arquivo é consistente ou seja, se é '1'
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

    // Lê o número de consultas a serem feitas
    int n;
    if (scanf("%d", &n) != 1)
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(p_bin);
        return;
    }

    // Loop para ler as consultas e processar cada uma
    for (int iter = 0; iter < n; iter++)
    {
        // Lê o número de campos a serem pesquisados
        int m = 0;
        scanf(" %d", &m);

        // Array auxiliar para informar quais campos devem ser pesquisados e comparados com o filtro
        bool pesquisa[PUBLIC_FIELDS];
        for (int i = 0; i < PUBLIC_FIELDS; i++) // inicializa o array de pesquisa como false
            pesquisa[i] = 0;

        // Struct registro auxiliar para ler o binario
        REG filtro;

        // String auxiliar para ler o valor do campo a ser pesquisado
        char str[41];

        for (int i = 0; i < m; i++)
        {
            // Le o campo a ser pesquisado e coloca em um buffer
            char field[41];
            if (scanf(" %s", field) != 1)
            {
                printf("Campo não existente.\n");
                fclose(p_bin);
                return;
            }
            // Joga esse buffer para o "hash" retorna op
            int op = field_to_index(field);
            // Verifica se o campo lido é válido, ou seja, se o op retornado é diferente de -1
            if (op == -1)
            {
                printf("Campo não existente.\n");
                return;
            }

            // Seta como true a posição do campo a ser pesquisado para saber qual(is) campo(s) comparar com o filtro depois
            pesquisa[op] = true;

            // Limpa o buffer
            str[0] = '\0';

            // Le o valor do campo a ser pesquisado e coloca no buffer
            ScanQuoteString(str);
            // Coloca no registro filtro os valores lidos para comparar com os registros do arquivo binário depois
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

            // Lê o registro do arquivo binário para a struct registro
            read_from_bin(p_bin, &registro);

            // Verifica se o registro está removido , e se estiver não printa
            if (registro.removido == '0')
            {
                if (match_filtro(&registro, pesquisa, &filtro))
                {
                    // Printa o registro no terminal caso ele bata com o filtro e seta encontrou como true para no final verificar se pelo menos um registro bateu com o filtro
                    print_registro_in_terminal(&registro);
                    encontrou = true;
                }
            }
        }

        // Verifica se encontrou algum registro que bateu com o filtro ou se nao havia registros para serem lidos
        if (count_regs == 0 || !encontrou)
        {
            printf("Registro inexistente.\n");
        }

        // Separa as consultas por uma linha em branco
        printf("\n");
    }

    // Fecha os arquivos
    fclose(p_bin);
    p_bin = NULL;
}
