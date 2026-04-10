#include <stdio.h>
#include <stdbool.h>
#include "IO.h"
#include "filtro.h"
#include "registro.h"

void insert_from_where()
{
    // Lê o nome do arquivo binário
    char bin_name[41];
    scanf("%s", bin_name);

    // Tenta abrir o arquivo para leitura e escrita em modo binário
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
        printf("Falha no processamento do arquivo3.\n");
        fclose(p_bin);
        return;
    }

    // Define o arquivo binário como inconsistente no registro de cabeçalho durante a escrita
    status = '0';
    fseek(p_bin, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, p_bin);

    // Lê o número de registros a serem inseridos
    int n;
    if (scanf("%d", &n) != 1)
        return;

    // Loop para ler os registros a serem inseridos e processar cada um
    for (int i = 0; i < n; i++)
    {
        // Struct registro auxiliar para ler o binario
        REG new_registro;

        // Lê os valores do novo registro a ser inserido
        read_new_registro_from_terminal(&new_registro);

        // Inicializa os campos de removido e proximo do novo registro
        new_registro.removido = '0';
        new_registro.proximo = -1;

        // Vai para o 1 byte do cabecalho (topo) para pegar o topo da pilha de registros removidos para inserir o novo registro
        fseek(p_bin, 1, SEEK_SET);
        // Pega o topo da pilha de registros removidos para inserir o novo registro
        int topo = -1;
        if (fread(&topo, sizeof(int), 1, p_bin) != 1)
        {
            printf("Falha no processamento do arquivo.\n");
            fclose(p_bin);
            return;
        }

        // Vai para o 5 byte do cabecalho (proxRRN) para pegar quantos registros existem
        fseek(p_bin, 5, SEEK_SET);
        int ProxRRN = 0;
        if (fread(&ProxRRN, sizeof(int), 1, p_bin) != 1)
        {
            printf("Falha no processamento do arquivo.\n");
            fclose(p_bin);
            return;
        }

        // Se a pilha de removidos estiver vazia, insere o novo registro no final do arquivo
        if (topo == -1)
        {
            // Vai para o primeiro byteoffset do registro de RRN ProxRRN e escreve o novo registro no arquivo
            fseek(p_bin, ProxRRN * 80 + 17, SEEK_SET);
            write_in_bin(p_bin, &new_registro);

            // Atualiza o próximo RRN
            ProxRRN++;
            // Vai para o 5 byte do cabecalho (proxRRN) para atualizar quantos registros existem
            fseek(p_bin, 5, SEEK_SET);
            fwrite(&ProxRRN, sizeof(int), 1, p_bin);
        }
        else
        {
            // Guarda o valor do topo antigo para depois acessar onde o novo registro será inserido
            int topo_antigo = topo;
            // Se a pilha de removidos não estiver vazia, le o novo topo
            fseek(p_bin, topo_antigo* 80 + 18, SEEK_SET);
            if (fread(&topo, sizeof(int), 1, p_bin) != 1)
            {
                printf("Falha no processamento do arquivo.\n");
                fclose(p_bin);
                return;
            }

            // Vai para o local do novo registro e escreve ele no arquivo
            fseek(p_bin, topo_antigo * 80 + 17, SEEK_SET);
            write_in_bin(p_bin, &new_registro);

            // Vai para o 1 byte do cabecalho (topo) para atualizar o topo da pilha de removidos
            fseek(p_bin, 1, SEEK_SET);
            fwrite(&topo, sizeof(int), 1, p_bin);
        }

    }

    // Atualiza o número de estações e pares de estações no registro de cabeçalho
    atualizar_estacoes(p_bin);

    // Vai para o 0 byte do cabecalho (status) para atualizar o status
    status = '1';
    fseek(p_bin, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, p_bin);

    // Fecha os arquivos
    fclose(p_bin);
    p_bin = NULL;

    // Chama a função binarioNaTela
    BinarioNaTela(bin_name);
}
