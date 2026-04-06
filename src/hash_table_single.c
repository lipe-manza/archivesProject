#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/hash_tables.h"

// Nó
struct node_s
{
    char e1[41]; // string fixa
    struct node_s *next_node_s;
};

// Bucket
struct bucket_s
{
    ND_S *colisao;
};

// Hash table
struct hash_table_s
{
    BU_S *bucket_s;
    int count;
};

// Função hash (djb2)
unsigned int hash_single(char *str)
{
    unsigned long hash = 5381;
    int i = 0;

    while (str[i] != '\0')
    {
        hash = ((hash << 5) + hash) + str[i];
        i++;
    }

    return hash % TABLE_SIZE;
}

// Construtor
HASH_S *hash_table_single()
{
    HASH_S *hash_table_s = malloc(sizeof(HASH_S));
    if (!hash_table_s)
        return NULL;

    hash_table_s->bucket_s = malloc(TABLE_SIZE * sizeof(BU_S));
    if (!hash_table_s->bucket_s)
    {
        free(hash_table_s);
        return NULL;
    }

    for (int i = 0; i < TABLE_SIZE; i++)
        hash_table_s->bucket_s[i].colisao = NULL;

    hash_table_s->count = 0;
    return hash_table_s;
}

// Inserção
void hash_table_single_insert(HASH_S *hash_table_s, char *e1)
{
    if (!hash_table_s || !e1)
        return;

    int key = hash_single(e1);
    ND_S *p = hash_table_s->bucket_s[key].colisao;

    // Verifica duplicado
    while (p != NULL)
    {
        if (strcmp(p->e1, e1) == 0)
            return;
        p = p->next_node_s;
    }

    ND_S *new_node_s = malloc(sizeof(ND_S));
    if (!new_node_s)
        return;

    // Copia no máximo 40 caracteres e reserva o último para o '\0'
    strncpy(new_node_s->e1, e1, 40);
    new_node_s->e1[40] = '\0'; // strncpy não garante o null-terminator se truncar

    new_node_s->next_node_s = hash_table_s->bucket_s[key].colisao;
    hash_table_s->bucket_s[key].colisao = new_node_s;

    hash_table_s->count++;
}

// Liberar memória
void hash_table_single_free(HASH_S **hash_table_s)
{
    if (!hash_table_s || !*hash_table_s)
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

// Contagem
int hash_table_single_get_count(HASH_S *hash)
{
    return hash ? hash->count : 0;
}
