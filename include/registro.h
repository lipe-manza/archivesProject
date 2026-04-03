#ifndef REG_H
#define REG_H

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

REG* novo_registro();
void free_registro(REG** r);

char get_removido(REG *r);
int get_proximo(REG *r);
int get_codEstacao(REG *r);
int get_codLinha(REG *r);
int get_codProxEstacao(REG *r);
int get_distProxEstacao(REG *r);
int get_codLinhaIntegra(REG *r);
int get_codEstIntegra(REG *r);
int get_tamNomeEstacao(REG *r);
const char* get_nomeEstacao(REG *r);
int get_tamNomeLinha(REG *r);
const char* get_nomeLinha(REG *r);

void set_removido(REG *r, char valor);
void set_proximo(REG *r, int valor);
void set_codEstacao(REG *r, int valor);
void set_codLinha(REG *r, int valor);
void set_codProxEstacao(REG *r, int valor);
void set_distProxEstacao(REG *r, int valor);
void set_codLinhaIntegra(REG *r, int valor);
void set_codEstIntegra(REG *r, int valor);
void set_nomeEstacao(REG *r, const char *nome);
void set_nomeLinha(REG *r, const char *nome);

#endif
