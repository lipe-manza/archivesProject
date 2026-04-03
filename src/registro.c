#include "../include/registro.h"

struct registro
{
    char removido;
    int proximo;
    int codEstacao;
    int codLinha;
    int codProxEstacao;
    int distProxEstacao;
    int codLinhaIntegra;
    int codEstIntegra;
    int tamNomeEstacao;
    char nomeEstacao[41];
    int tamNomeLinha;
    char nomeLinha[41];
};

REG *novo_registro()
{
    REG *r = malloc(1 * sizeof(REG));

    if (!r)
        return NULL;

    r->removido = '0';
    r->proximo = -1;
    r->codEstacao = -1;
    r->codLinha = -1;
    r->codProxEstacao = -1;
    r->distProxEstacao = -1;
    r->codLinhaIntegra = -1;
    r->codEstIntegra = -1;

    r->tamNomeEstacao = 0;
    r->nomeEstacao[0] = '\0';

    r->tamNomeLinha = 0;
    r->nomeLinha[0] = '\0';

    return r;
}

void free_registro(REG **r)
{
    free(*r);
    r = NULL;
}

char get_removido(REG *r) { return r->removido; }
int get_proximo(REG *r) { return r->proximo; }
int get_codEstacao(REG *r) { return r->codEstacao; }
int get_codLinha(REG *r) { return r->codLinha; }
int get_codProxEstacao(REG *r) { return r->codProxEstacao; }
int get_distProxEstacao(REG *r) { return r->distProxEstacao; }
int get_codLinhaIntegra(REG *r) { return r->codLinhaIntegra; }
int get_codEstIntegra(REG *r) { return r->codEstIntegra; }
int get_tamNomeEstacao(REG *r) { return r->tamNomeEstacao; }
const char *get_nomeEstacao(REG *r) { return r->nomeEstacao; }
int get_tamNomeLinha(REG *r) { return r->tamNomeLinha; }
const char *get_nomeLinha(REG *r) { return r->nomeLinha; }

void set_removido(REG *r, char valor) { r->removido = valor; }
void set_proximo(REG *r, int valor) { r->proximo = valor; }
void set_codEstacao(REG *r, int valor) { r->codEstacao = valor; }
void set_codLinha(REG *r, int valor) { r->codLinha = valor; }
void set_codProxEstacao(REG *r, int valor) { r->codProxEstacao = valor; }
void set_distProxEstacao(REG *r, int valor) { r->distProxEstacao = valor; }
void set_codLinhaIntegra(REG *r, int valor) { r->codLinhaIntegra = valor; }
void set_codEstIntegra(REG *r, int valor) { r->codEstIntegra = valor; }

void set_nomeEstacao(REG *r, const char *nome)
{
    if (nome != NULL)
    {
        strncpy(r->nomeEstacao, nome, 40);
        r->nomeEstacao[40] = '\0';
        r->tamNomeEstacao = strlen(r->nomeEstacao);
    }
}

void set_nomeLinha(REG *r, const char *nome)
{
    if (nome != NULL)
    {
        strncpy(r->nomeLinha, nome, 40);
        r->nomeLinha[40] = '\0';
        r->tamNomeLinha = strlen(r->nomeLinha);
    }
}
