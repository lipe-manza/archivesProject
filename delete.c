#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "sql_functions.h"
#include "filtro.h"
#include "IO.h"

void delete_from_where()
{
    char bin_name[41];
    scanf("%s", bin_name);

    // Abre o arquivo para leitura e escrita em modo binário
    FILE *p_bin = fopen(bin_name, "rb+");
    if (p_bin == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // Lê o status do arquivo para verificar se ele está consistente
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

    // Define o arquivo binário como inconsistente no registro de cabeçalho durante a escrita
    fseek(p_bin, 0, SEEK_SET);
    status = '0';
    fwrite(&status, sizeof(char), 1, p_bin);

    // Array auxiliar para informar quais campos devem ser pesquisados e comparados com o filtro
    int n;
    if (scanf("%d", &n) != 1)
        return;
    for (int i = 0; i < n; i++)
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

        for (int j = 0; j < m; j++)
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

            // Seta como true a pesquisa do campo op
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
            if (registro.removido == '1')
                continue;

            if (match_filtro(&registro, pesquisa, &filtro))
            {
                // Remoção lógica
                int topo = -1;
                char removido = '1';

                // Lê o topo da pilha de registros removidos indicado
                fseek(p_bin, 1, SEEK_SET);
                if (fread(&topo, sizeof(int), 1, p_bin) != 1)
                {
                    printf("Falha no processamento do arquivo.\n");
                    fclose(p_bin);
                    return;
                }

                // Define o registro atual como removido
                fseek(p_bin, RRN * 80 + 17, SEEK_SET);
                fwrite(&removido, sizeof(char), 1, p_bin);

                // Atribui ao campo próximo do registro o valor anterior do topo da pilha de registros removidos
                fwrite(&topo, sizeof(int), 1, p_bin);

                // Define o topo da pilha como o RRN do último registro removido
                fseek(p_bin, 1, SEEK_SET);
                fwrite(&RRN, sizeof(int), 1, p_bin);
            }
        }

        // Atualiza  o numero de estacoes e de pares de estacoes
    }
    
    atualizar_estacoes(p_bin);

    // Define o arquivo binário como consistente no registro de cabeçalho
    status = '1';
    fseek(p_bin, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, p_bin);
    // Fecha os arquivos
    fclose(p_bin);
    p_bin = NULL;

    BinarioNaTela(bin_name);
}
