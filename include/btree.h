#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>
#include <stdio.h>

// ==================== Constantes ====================

// Ordem e limites da árvore B
#define BTREE_ORDER 4
#define BTREE_MAX_KEYS 3
#define BTREE_MAX_CHILDREN 4
#define BTREE_MIN_KEYS 1

// Tamanhos do cabeçalho e página no arquivo
#define BTREE_HEADER_SIZE 17
#define BTREE_PAGE_SIZE 53

// Tipos de página
#define PAGE_TYPE_LEAF -1
#define PAGE_TYPE_ROOT 0
#define PAGE_TYPE_MID 1

// Retornos possíveis das operações
#define BTREE_PROMOTION 1
#define BTREE_NO_PROMOTION 0
#define BTREE_ERROR -1
#define BTREE_NOT_FOUND -1

// ==================== Estruturas ====================

// Estrutura simples para transportar chave e referência no arquivo
typedef struct {
  int C;  // chave (codEstacao)
  int Pr; // posição no arquivo de dados
} BTreeKey;

// Estrutura do cabeçalho da árvore
typedef struct {
  char status; // '0' = inconsistente, '1' = consistente
  int noRaiz;  // RRN do nó raiz. -1 se vazia
  int topo;    // RRN do topo da pilha de removidos. -1 se vazia
  int proxRRN; // Próximo RRN disponível para criação de nó
  int nroNos;  // Número total de nós (páginas) na árvore
} BTreeHeader;

// Estrutura de uma página/nó da árvore
typedef struct {
  char removido;                   // '1' = removido, '0' = ativo
  int proximo;                     // RRN da próxima página removida
  int tipoNo;                      // -1 = Folha, 0 = Raiz, 1 = Intermediário
  int nroChaves;                   // Quantidade de chaves presentes
  BTreeKey chaves[BTREE_MAX_KEYS]; // Chaves (C) e offsets (Pr)
  int P[BTREE_MAX_CHILDREN];       // Ponteiros para subárvores (RRNs)
} BTreePage;

// ==================== Leitura e Escrita em Disco ====================

bool btree_header_read(FILE *bin_file, BTreeHeader *header);
bool btree_header_write(FILE *bin_file, const BTreeHeader *header);

bool btree_page_read(FILE *bin_file, BTreePage *page, int rrn);
bool btree_page_write(FILE *bin_file, const BTreePage *page, int rrn);

// ==================== Operações principais ====================

// Insere uma chave na árvore B (com split se necessário)
bool btree_insert_key(FILE *bin_file, BTreeHeader *header, BTreeKey key);

// Busca uma chave e retorna sua posição no arquivo de dados
int btree_search_key(FILE *bin_file, BTreeHeader *header, int search_key);

// Remove uma chave da árvore (tratando redistribuição e merge)
bool btree_delete_key(FILE *bin_file, BTreeHeader *header, int key_to_delete);

#endif // BTREE_H
