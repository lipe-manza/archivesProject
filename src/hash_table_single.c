#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/hash_table_single.h"

// No
struct node
{
    int e1;
    struct node *next_node;
};

// Bucket da tabela hash
struct bucket
{
    ND *colisao;
};

struct hash_table
{
    BU *buckets;
    int count; // elementos únicos
};

// Função hash
unsigned int hash_single(int e1)
{
    return (e1 % TABLE_SIZE);
}

// Construtor
HASH_S *hash_table_single()
{
    HASH_S *hash_table = malloc(sizeof(HASH_S));

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

    hash_table->count = 0;

    return hash_table;
}

// Inserção
void hash_table_single_insert(HASH_S *hash_table, int e1)
{
    if (!hash_table)
        return;

    int key = hash_single(e1);
    ND *p = hash_table->buckets[key].colisao;

    // verifica duplicado
    while (p != NULL)
    {
        if (p->e1 == e1)
            return;
        p = p->next_node;
    }

    ND *new_node = malloc(sizeof(ND));
    if (!new_node)
        return;

    new_node->e1 = e1;
    new_node->next_node = hash_table->buckets[key].colisao;
    hash_table->buckets[key].colisao = new_node;

    hash_table->count++;
}

// Liberar memoria
void hash_table_single_free(HASH_S *hash_table)
{
    if (!hash_table)
        return;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        ND *aux = hash_table->buckets[i].colisao;

        while (aux)
        {
            ND *tmp = aux->next_node;
            free(aux);
            aux = tmp;
        }
    }

    free(hash_table->buckets);
    free(hash_table);
}

int hash_table_single_get_count(HASH_S *hash)
{
    return hash->count;
}
