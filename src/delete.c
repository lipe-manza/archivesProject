#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/sql_functions.h"
#include "../include/filtro.h"
#include "../include/IO.h"

bool delete_from_where(char *bin_name)
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
            return false;
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

    FILE *p_bin = fopen(bin_name, "rb+"); // Abre o arquivo para leitura e escrita em modo binário
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
            if (match_filtro(&registro, pesquisa, &filtro))
            {
                // Remoção lógica
                int topo = -1;
                char removido = '1';

                // Lê o topo da pilha de registros removidos indicado
                fseek(p_bin, 1, SEEK_SET);
                fread(&topo, sizeof(int), 1, p_bin);

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
    }

    // Define o arquivo binário como consistente no registro de cabeçalho
    status = '1';
    fwrite(&status, sizeof(char), 1, p_bin);

    // Fecha os arquivos
    fclose(p_bin);
    p_bin = NULL;

    return true;
}
