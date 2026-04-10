#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_tables.h"

#define TABLE_SIZE 1009

// Struct
typedef struct nodeEstacao
{
    char nomeEstacao[MAX_NOME];
    struct nodeEstacao *next;
} NDEST;

struct hash_estacao
{
    NDEST *buckets[TABLE_SIZE];
    int count;
};

typedef struct nodePar
{
    int codA;
    int codB;
    struct nodePar *next;
} NDPAR;

struct hash_par
{
    NDPAR *buckets[TABLE_SIZE];
    int count;
};

//  Função hash para strings usando o algoritmo djb2
static unsigned int hash_string(const char *str)
{
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % TABLE_SIZE;
}

// Função hash para pares de inteiros
static unsigned int _hash_int_pair(int c1, int c2)
{
    // Variaveis para garantir que a ordem dos códigos não importe
    int minn = c1 < c2 ? c1 : c2;
    int maxx = c1 > c2 ? c1 : c2;

    // Combinação simples dos dois inteiros para gerar um hash, usando números primos para reduzir colisões
    return (unsigned int)((minn * 31) + (maxx * 17)) % TABLE_SIZE;
}

// Construtor da hash de estações
HashEstacao *criar_hash_estacao()
{
    HashEstacao *ht = (HashEstacao *)calloc(1, sizeof(HashEstacao));
    return ht;
}

int inserir_estacao(HashEstacao *ht, const char *nome)
{
    // Verifica se a hash table ou o nome são nulos, e retorna 0 para indicar falha
    if (!ht || !nome)
        return 0;

    // Calcula o hash do nome da estação e retorna o índice da bucket correspondente
    unsigned int key = hash_string(nome);

    // Percorre a lista encadeada da bucket para verificar se a estação já existe
    NDEST *curr = ht->buckets[key];
    while (curr)
    {
        // Se a estação já existe, retorna 0 para indicar que a inserção não foi realizada
        if (strcmp(curr->nomeEstacao, nome) == 0)
            return 0;
        curr = curr->next;
    }

    // Se chegou aqui, a estação é nova e deve ser inserida no início da lista encadeada da bucket
    NDEST *novo = (NDEST *)malloc(sizeof(NDEST));
    // strncpy(novo->nomeEstacao, nome, MAX_NOME - 1);
    // novo->nomeEstacao[MAX_NOME - 1] = '\0'; // Garantir terminação nula
    strcpy(novo->nomeEstacao, nome);
    novo->next = ht->buckets[key];
    ht->buckets[key] = novo;
    ht->count++;
    return 1;
}

int get_nro_estacoes(HashEstacao *ht)
{
    return ht ? ht->count : 0;
}

// Construtor da hash de pares de estações
HashPar *criar_hash_par()
{
    return (HashPar *)calloc(1, sizeof(HashPar));
}

int inserir_par(HashPar *ht, int c1, int c2)
{
    // Verifica se a hash table é nula, e retorna 0 para indicar falha
    if (!ht)
        return 0;

    // Ignorar pares inválidos (com -1)
    if (c1 == -1 || c2 == -1)
        return 0;

    // Calcula o hash do par de estações e retorna o índice da bucket correspondente
    unsigned int key = _hash_int_pair(c1, c2);
    NDPAR *curr = ht->buckets[key];

    // Percorre a lista encadeada da bucket para verificar se o par de estações já existe
    while (curr)
    {
        // Compara os códigos das estações onde a ordem não importa
        if ((curr->codA == c1 && curr->codB == c2) || (curr->codA == c2 && curr->codB == c1))
            return 0;
        curr = curr->next;
    }

    // Se chegou aqui, o par é unico
    // Aloca um novo nó e verifica se a alocação deu certo
    NDPAR *novo = (NDPAR *)malloc(sizeof(NDPAR));
    if (!novo)
        return 0;

    // Insere o novo par no início da lista encadeada da bucket
    novo->codA = c1;
    novo->codB = c2;
    novo->next = ht->buckets[key];
    ht->buckets[key] = novo;

    // Incrementa a contagem de pares únicos
    ht->count++;

    return 1;
}

int get_nro_pares(HashPar *ht)
{
    return ht ? ht->count : 0;
}

// Função para liberar a memória da hash de estações
void free_hash_estacao(HashEstacao *ht)
{
    if (!ht)
        return;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        NDEST *curr = ht->buckets[i];
        while (curr)
        {
            NDEST *aux = curr;
            curr = curr->next;
            free(aux);
        }
    }
    free(ht);
}

// Função para liberar a memória da hash de pares de estações
void free_hash_par(HashPar *ht)
{
    if (!ht)
        return;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        NDPAR *curr = ht->buckets[i];
        while (curr)
        {
            NDPAR *aux = curr;
            curr = curr->next;
            free(aux);
        }
    }
    free(ht);
}
