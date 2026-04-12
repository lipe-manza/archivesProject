#include "IO.h"
#include "filtro.h"
#include "registro.h"
#include "sql_functions.h"
#include <stdbool.h>
#include <stdio.h>

void update_set_where()
{
    // Variável para guardar o nome do arquivo .bin
    char bin_name[50];

    // Lê o nome do arquivo binário
    if (scanf("%s", bin_name) != 1){
        printf("Falha na leitura do nome do arquivo.\n");
        return;
    }

    // Abre o arquivo .bin para leitura e escrita e verifica se a abertura
    // foi bem sucedida conferindo o status do arquivo
    FILE *f_bin = open_bin(bin_name, "rb+");
    if (f_bin == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Define o arquivo binário como inconsistente no registro de cabeçalho
    // durante a escrita
    char status = '0';
    fwrite(&status, sizeof(char), 1, f_bin);

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

    // Lê o número de atualizações a serem feitas
    int n;
    if (scanf("%d", &n) != 1)
        return;

    // Itera sobre as sessões de atualização
    for (int i = 0; i < n; i++)
    {
        // Struct registro que serve como comparação para filtrar
        // os registros do arquivo .bin
        REG filter;

        // Array auxiliar para informar quais campos devem ser pesquisados e
        // comparados com o filtro
        bool search[PUBLIC_FIELDS];

        // Preenche a struct filter e o array search com os valores do filtro de pesquisa
        filter_build(&filter, search);

        // Registro que guarda os valores a serem atualizados
        REG updated;

        // Array auxiliar para informar quais campos devem ser atualizados
        bool update[PUBLIC_FIELDS];

        // Preenche a struct updated e o array update com os valores a serem atualizados
        filter_build(&updated, update);

        // Struct registro auxiliar para ler o binario
        REG registro;

        // Itera pelos registros do .bin
        for (int RRN = 0; RRN < reg_count; RRN++)
        {
            // Vai para o byteoffset do registro atual
            fseek(f_bin, RRN * 80 + 17, SEEK_SET);

            // Lê o registro do .bin para a struct registro
            read_from_bin(f_bin, &registro);

            // Se o registro está removido ele é pulado
            if (registro.removido == '1')
                continue;

            if (match_filter(&registro, search, &filter))
                atualizar_registro(&registro, &updated, update, RRN, f_bin);
        }
    }

    // Atualiza o número de estações e pares de estações no registro de
    // cabeçalho
    atualizar_estacoes(f_bin);

    // Define o arquivo binário como consistente no registro de cabeçalho
    fseek(f_bin, 0, SEEK_SET);
    status = '1';
    fwrite(&status, sizeof(char), 1, f_bin);

    // Fecha o arquivo .bin
    fclose(f_bin);
    f_bin = NULL;

    BinarioNaTela(bin_name);
}
