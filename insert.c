#include <stdio.h>
#include <stdbool.h>
#include "IO.h"
#include "filtro.h"
#include "registro.h"

bool insert_from_where(char *bin_name)
{

    // Struct registro auxiliar para ler o binario
    REG new_registro;

    read_new_registro_from_terminal(&new_registro);

    // Inicializa os campos de removido e proximo do novo registro
    new_registro.removido = '0';
    new_registro.proximo = -1;


    FILE *p_bin = fopen(bin_name, "rb+"); // Tenta criar .bin para escrita binaria
    if (p_bin == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        return false;
    }

    // Escreve o status do arquivo como '0' para indicar que ele está inconsistente durante a escrita
    char status;
    fread(&status, sizeof(char), 1, p_bin);
    if (status == '0')
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(p_bin);
        return false;
    }

    // Pega o topo da pilha de registros removidos para inserir o novo registro
    int topo = -1;
    fread(&topo, sizeof(int), 1, p_bin);
    // Vai para o 5 byte do cabecalho (proxRRN) para pegar quantos registros existem
    int ProxRRN = 0;

    fread(&ProxRRN, sizeof(int), 1, p_bin);

    // Se a pilha de removidos estiver vazia, insere o novo registro no final do arquivo
    if (topo == -1)
    {
        fseek(p_bin, ProxRRN * 80 + 17, SEEK_END);
        write_in_bin(p_bin, &new_registro);

        ProxRRN++;
        // Vai para o 5 byte do cabecalho (proxRRN) para atualizar quantos registros existem
        fseek(p_bin, 5, SEEK_SET);
        fwrite(&ProxRRN, sizeof(int), 1, p_bin);
    }
    else
    {

        // Se a pilha de removidos não estiver vazia, le o novo topo
        fseek(p_bin, topo * 80 + 18, SEEK_SET);
        fread(&topo, sizeof(int), 1, p_bin);

        // Vai para o local do novo registro e escreve ele no arquivo
        fseek(p_bin, topo * 80 + 17, SEEK_SET);
        write_in_bin(p_bin, &new_registro);

        // Vai para o 1 byte do cabecalho (topo) para atualizar o topo da pilha de removidos
        fseek(p_bin, 1, SEEK_SET);
        fwrite(&topo, sizeof(int), 1, p_bin);
    }

    atualizar_estacoes(p_bin);

    status = '1';
    // Vai para o 0 byte do cabecalho (status) para atualizar o status
    fseek(p_bin, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, p_bin);

    // Fecha os arquivos
    fclose(p_bin);
    p_bin = NULL;

    return true;
}
