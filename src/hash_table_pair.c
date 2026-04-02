#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/hash_table_pair.h"


// No colisao
struct node
{
    int e1;
    int e2;
    struct node *next_node;
};

// Estrutura do bucket da tabela hash
struct bucket
{
    ND *colisao;
};

struct hash_table
{
    BU *buckets;
    int pairCount;
};

// Função hash
unsigned int hash_pair(int e1, int e2)
{
    return (e1 * 1000 + e2) % TABLE_SIZE;
}

HASH_P *hash_table_pair()
{
    HASH_P *hash_table = malloc(sizeof(HASH_P));

    if (hash_table == NULL)
        return NULL;

    hash_table->buckets = malloc(TABLE_SIZE * sizeof(BU));

    if (hash_table->buckets == NULL)
    {
        free(hash_table);
        return NULL;
    }

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table->buckets[i].colisao = NULL;
    }

    hash_table->pairCount = 0;

    return hash_table;
}

void hash_table_pair_insert(HASH_P *hash_table, int e1, int e2)
{
    if (!hash_table) return;

    int key = hash_pair(e1, e2);
    ND *p = hash_table->buckets[key].colisao;

    // verifica par duplicado
    while (p != NULL)
    {
        if (p->e1 == e1 && p->e2 == e2)
            return;
        p = p->next_node;
    }

    ND *new_node = malloc(sizeof(ND));
    if (!new_node) return;

    new_node->e1 = e1;
    new_node->e2 = e2;

    // insere no inicio
    new_node->next_node = hash_table->buckets[key].colisao;
    hash_table->buckets[key].colisao = new_node;

    hash_table->pairCount++;
}

// Função para liberar a memória alocada para a tabela hash
void hash_table_pair_free(HASH_P **hash_table)
{
    if (!hash_table)
        return;

    if(!*hash_table)
        return;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        ND *aux = (*hash_table)->buckets[i].colisao;

        while (aux)
        {
            ND *tmp = aux->next_node;
            free(aux);
            aux = tmp;
        }
    }

    free((*hash_table)->buckets);
    free(*hash_table);
    *hash_table = NULL;
}
int hash_table_pair_get_count(HASH_P *hash){
    return hash->pairCount;
}
