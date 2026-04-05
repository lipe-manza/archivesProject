#ifndef REG_H
#define REG_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct registro
{
    char removido; // '1' para removido e '0' para nao removido
    int proximo;
    int codEstacao; // Não pode ser nulo
    int codLinha;
    int codProxEstacao;
    int distProxEstacao;
    int codLinhaIntegra;
    int codEstIntegra;
    int tamNomeEstacao;   // Se for 0 não escrever o nomeEstacao
    char nomeEstacao[41]; // Não pode ser nulo
    int tamNomeLinha;
    char nomeLinha[41];
} REG;



void read_from_bin(FILE *p_bin, REG *reg);
void write_in_bin(FILE *p_bin, REG *reg);
void atualizar_registro(REG *atualizado, bool atualizar[], int RRN, FILE *p_bin);

#endif
