#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/hash_tables.h"

// No
struct node_s
{
    int e1;
    struct node_s *next_node_s;
};

// Bucket da tabela hash
struct bucket_s
{
    ND_S *colisao;
};

struct hash_table_s
{
    BU_S *bucket_s;
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
    HASH_S *hash_table_s = malloc(sizeof(HASH_S));

    if (hash_table_s == NULL)
        return NULL;

    hash_table_s->bucket_s = malloc(TABLE_SIZE * sizeof(BU_S));

    if (hash_table_s->bucket_s == NULL)
    {
        free(hash_table_s);
        return NULL;
    }

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table_s->bucket_s[i].colisao = NULL;
    }

    hash_table_s->count = 0;

    return hash_table_s;
}

// Inserção
void hash_table_single_insert(HASH_S *hash_table_s, int e1)
{
    if (!hash_table_s)
        return;

    int key = hash_single(e1);
    ND_S *p = hash_table_s->bucket_s[key].colisao;

    // verifica duplicado
    while (p != NULL)
    {
        if (p->e1 == e1)
            return;
        p = p->next_node_s;
    }

    ND_S *new_node_s = malloc(sizeof(ND_S));
    if (!new_node_s)
        return;

    new_node_s->e1 = e1;
    new_node_s->next_node_s = hash_table_s->bucket_s[key].colisao;
    hash_table_s->bucket_s[key].colisao = new_node_s;

    hash_table_s->count++;
}

// Liberar memoria
void hash_table_single_free(HASH_S **hash_table_s)
{
    if (!hash_table_s)
        return;

    if (!*hash_table_s)
        return;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        ND_S *aux = (*hash_table_s)->bucket_s[i].colisao;

        while (aux)
        {
            ND_S *tmp = aux->next_node_s;
            free(aux);
            aux = tmp;
        }
    }

    free((*hash_table_s)->bucket_s);
    free(*hash_table_s);
    *hash_table_s = NULL;
}

int hash_table_single_get_count(HASH_S *hash)
{
    return hash->count;
}
