#include <stdlib.h>
#include <string.h>

#include "../../include/hash_tables.h"

#define TABLE_SIZE 1009

// Estrutura do nó da lista encadeada para nomes de estações
typedef struct node_station {
  char nomeEstacao[MAX_NOME];
  struct node_station *next;
} NodeStation;

struct hash_estacao {
  NodeStation *buckets[TABLE_SIZE];
  int count;
};

// Estrutura do nó da lista encadeada para pares de inteiros
typedef struct node_pair {
  int codA;
  int codB;
  struct node_pair *next;
} NodePair;

struct hash_par {
  NodePair *buckets[TABLE_SIZE];
  int count;
};

/**
 * @brief Função hash para strings usando o algoritmo djb2.
 */
static unsigned int hash_string(const char *str) {
  unsigned int hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;
  return hash % TABLE_SIZE;
}

/**
 * @brief Função hash para pares de inteiros.
 */
static unsigned int hash_int_pair(int c1, int c2) {
  // Ordena os códigos para que (A,B) e (B,A) gerem o mesmo hash
  int minn = c1 < c2 ? c1 : c2;
  int maxx = c1 > c2 ? c1 : c2;

  // Combinação usando números primos para reduzir colisões
  return (unsigned int)((minn * 31) + (maxx * 17)) % TABLE_SIZE;
}

HashEstacao *criar_hash_estacao() {
  return (HashEstacao *)calloc(1, sizeof(HashEstacao));
}

int inserir_estacao(HashEstacao *ht, const char *nome) {
  if (!ht || !nome)
    return 0;

  unsigned int key = hash_string(nome);
  NodeStation *curr = ht->buckets[key];

  // Percorre a lista encadeada do bucket
  while (curr) {
    // Se a estação já existe, a inserção é ignorada (retorna 0)
    if (strcmp(curr->nomeEstacao, nome) == 0)
      return 0;
    curr = curr->next;
  }

  // Insere a nova estação no início do bucket
  NodeStation *new_node = (NodeStation *)malloc(sizeof(NodeStation));
  if (!new_node)
    return 0;

  strcpy(new_node->nomeEstacao, nome);
  new_node->next = ht->buckets[key];
  ht->buckets[key] = new_node;
  ht->count++;

  return 1;
}

int get_nro_estacoes(HashEstacao *ht) { return ht ? ht->count : 0; }

HashPar *criar_hash_par() { return (HashPar *)calloc(1, sizeof(HashPar)); }

int inserir_par(HashPar *ht, int c1, int c2) {
  if (!ht)
    return 0;

  // Ignora pares inválidos (onde pelo menos um é nulo/-1)
  if (c1 == -1 || c2 == -1)
    return 0;

  unsigned int key = hash_int_pair(c1, c2);
  NodePair *curr = ht->buckets[key];

  // Percorre a lista encadeada para verificar se o par já existe
  while (curr) {
    if ((curr->codA == c1 && curr->codB == c2) ||
        (curr->codA == c2 && curr->codB == c1)) {
      return 0;
    }
    curr = curr->next;
  }

  // Aloca e insere o par único
  NodePair *new_node = (NodePair *)malloc(sizeof(NodePair));
  if (!new_node)
    return 0;

  new_node->codA = c1;
  new_node->codB = c2;
  new_node->next = ht->buckets[key];
  ht->buckets[key] = new_node;
  ht->count++;

  return 1;
}

int get_nro_pares(HashPar *ht) { return ht ? ht->count : 0; }

void free_hash_estacao(HashEstacao *ht) {
  if (!ht)
    return;
  for (int i = 0; i < TABLE_SIZE; i++) {
    NodeStation *curr = ht->buckets[i];
    while (curr) {
      NodeStation *aux = curr;
      curr = curr->next;
      free(aux);
    }
  }
  free(ht);
}

void free_hash_par(HashPar *ht) {
  if (!ht)
    return;
  for (int i = 0; i < TABLE_SIZE; i++) {
    NodePair *curr = ht->buckets[i];
    while (curr) {
      NodePair *aux = curr;
      curr = curr->next;
      free(aux);
    }
  }
  free(ht);
}
