#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_tables.h"

#define TABLE_SIZE 1009

// --- Estruturas Internas (Ocultas do usuário) ---

typedef struct NodeEstacao
{
    char nomeEstacao[MAX_NOME];
    struct NodeEstacao *next;
} NodeEstacao;

struct hash_estacao
{
    NodeEstacao *buckets[TABLE_SIZE];
    int count;
};

typedef struct NodePar
{
    int codA;
    int codB;
    struct NodePar *next;
} NodePar;

struct hash_par
{
    NodePar *buckets[TABLE_SIZE];
    int count;
};

// --- Funções Auxiliares de Hash ---

static unsigned int hash_string(const char *str)
{
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % TABLE_SIZE;
}

static unsigned int _hash_int_pair(int c1, int c2)
{
    int minn = c1 < c2 ? c1 : c2;
    int maxx = c1 > c2 ? c1 : c2;
    return (unsigned int)((minn * 31) + (maxx * 17)) % TABLE_SIZE;
}

// --- Implementação: Hash de Estações ---

HashEstacao *criar_hash_estacao()
{
    HashEstacao *ht = (HashEstacao *)calloc(1, sizeof(HashEstacao));
    return ht;
}

int inserir_estacao(HashEstacao *ht, const char *nome)
{
    if (!ht || !nome)
        return 0;
    unsigned int idx = hash_string(nome);

    NodeEstacao *curr = ht->buckets[idx];
    while (curr)
    {
        if (strcmp(curr->nomeEstacao, nome) == 0)
            return 0; // Já existe
        curr = curr->next;
    }

    NodeEstacao *novo = (NodeEstacao *)malloc(sizeof(NodeEstacao));
    strncpy(novo->nomeEstacao, nome, MAX_NOME - 1);
    novo->nomeEstacao[MAX_NOME - 1] = '\0';
    novo->next = ht->buckets[idx];
    ht->buckets[idx] = novo;
    ht->count++;
    return 1;
}

int get_nro_estacoes(HashEstacao *ht)
{
    return ht ? ht->count : 0;
}

// --- Implementação: Hash de Pares ---

HashPar *criar_hash_par()
{
    return (HashPar *)calloc(1, sizeof(HashPar));
}

int inserir_par(HashPar *ht, int c1, int c2)
{
    if (!ht)
        return 0;

    // Ignorar pares inválidos (com -1)
    if (c1 == -1 || c2 == -1)
        return 0;

    // A ordem não importa: (1, 2) == (2, 1)
    unsigned int idx = _hash_int_pair(c1, c2);
    NodePar *curr = ht->buckets[idx];

    while (curr)
    {
        // Comparação bidirecional: (1,2) == (2,1)
        if ((curr->codA == c1 && curr->codB == c2) || (curr->codA == c2 && curr->codB == c1))
            return 0; // Par idêntico já existe
        curr = curr->next;
    }

    // Se chegou aqui, o par é novo
    NodePar *novo = (NodePar *)malloc(sizeof(NodePar));
    if (!novo) return 0;

    novo->codA = c1;
    novo->codB = c2;
    novo->next = ht->buckets[idx];
    ht->buckets[idx] = novo;
    ht->count++;

    return 1;
}

int get_nro_pares(HashPar *ht)
{
    return ht ? ht->count : 0;
}

// --- Funções de Liberação de Memória ---

void free_hash_estacao(HashEstacao *ht)
{
    if (!ht)
        return;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        NodeEstacao *curr = ht->buckets[i];
        while (curr)
        {
            NodeEstacao *aux = curr;
            curr = curr->next;
            free(aux);
        }
    }
    free(ht);
}

void free_hash_par(HashPar *ht)
{
    if (!ht)
        return;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        NodePar *curr = ht->buckets[i];
        while (curr)
        {
            NodePar *aux = curr;
            curr = curr->next;
            free(aux);
        }
    }
    free(ht);
}
