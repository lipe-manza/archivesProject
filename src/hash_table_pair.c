#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/hash_tables.h"

// No colisao
struct node_p
{
    int e1;
    int e2;
    struct node_p *next_node_p;
};

// Estrutura do bucket_p da tabela hash
struct bucket_p
{
    ND_P *colisao;
};

struct hash_table_p
{
    BU_P *bucket_p;
    int pairCount;
};

// Função hash
unsigned int hash_pair(int e1, int e2)
{
    int minn = e1 < e2 ? e1 : e2;
    int maxx = e1 > e2 ? e1 : e2;
    return (minn * 1000 + maxx) % TABLE_SIZE;
}

HASH_P *hash_table_pair()
{
    HASH_P *hash_table_p = malloc(sizeof(HASH_P));

    if (hash_table_p == NULL)
        return NULL;

    hash_table_p->bucket_p = malloc(TABLE_SIZE * sizeof(BU_P));

    if (hash_table_p->bucket_p == NULL)
    {
        free(hash_table_p);
        return NULL;
    }

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table_p->bucket_p[i].colisao = NULL;
    }

    hash_table_p->pairCount = 0;

    return hash_table_p;
}

void hash_table_pair_insert(HASH_P *hash_table_p, int e1, int e2)
{
    if (!hash_table_p)
        return;

    int key = hash_pair(e1, e2);
    printf("Fez hash pair\n");
    ND_P *p = hash_table_p->bucket_p[key].colisao;
    printf("Declarou p\n");

    // verifica par duplicado
    while (p != NULL)
    {
        printf("p = %p\n", p);
        printf("p->e1 = %d\n", p->e1);
        printf("p->e2 = %d\n", p->e2);
        if ((p->e1 == e1 && p->e2 == e2) || (p->e1 == e2 && p->e2 == e1))
            return;
        p = p->next_node_p;
    }

    ND_P *new_node_p = malloc(sizeof(ND_P));
    if (!new_node_p)
        return;

    new_node_p->e1 = e1;
    new_node_p->e2 = e2;

    // insere no inicio
    new_node_p->next_node_p = hash_table_p->bucket_p[key].colisao;
    hash_table_p->bucket_p[key].colisao = new_node_p;

    hash_table_p->pairCount++;
}

// Função para liberar a memória alocada para a tabela hash
void hash_table_pair_free(HASH_P **hash_table_p)
{
    if (!hash_table_p)
        return;

    if (!*hash_table_p)
        return;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        ND_P *aux = (*hash_table_p)->bucket_p[i].colisao;

        while (aux)
        {
            ND_P *tmp = aux->next_node_p;
            free(aux);
            aux = tmp;
        }
    }

    free((*hash_table_p)->bucket_p);
    free(*hash_table_p);
    *hash_table_p = NULL;
}
int hash_table_pair_get_count(HASH_P *hash)
{
    return hash->pairCount;
}
