#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>
#include <stdio.h>

// ==================== Constantes e Macros ====================

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

// Estrutura do cabeçalho da árvore (opaca)
typedef struct btree_header_st BTreeHeader;

// Estrutura de uma página/nó da árvore (opaca)
typedef struct btree_page_st BTreePage;

// ==================== Criação e destruição ====================

// Cria o cabeçalho da árvore
BTreeHeader *btree_header_create(void);

// Libera o cabeçalho da memória
void btree_header_destroy(BTreeHeader **header);

// Cria uma nova página vazia
BTreePage *btree_page_create(void);

// Libera uma página da memória
void btree_page_destroy(BTreePage **page);

// ==================== Cabeçalho ====================

// Status do arquivo (consistente/inconsistente)
void btree_header_set_status(BTreeHeader *header, char status);
char btree_header_get_status(const BTreeHeader *header);

// Raiz da árvore
void btree_header_set_root_node(BTreeHeader *header, int root_node);
int btree_header_get_root_node(const BTreeHeader *header);

// Topo da pilha de páginas removidas
void btree_header_set_top_of_stack(BTreeHeader *header, int top_of_stack);
int btree_header_get_top_of_stack(const BTreeHeader *header);

// Próximo RRN disponível
void btree_header_set_next_rrn(BTreeHeader *header, int next_rrn);
int btree_header_get_next_rrn(const BTreeHeader *header);

// Quantidade de nós/páginas
void btree_header_set_node_count(BTreeHeader *header, int node_count);
int btree_header_get_node_count(const BTreeHeader *header);

// Leitura e escrita do cabeçalho no arquivo
bool btree_header_read(FILE *bin_file, BTreeHeader *header);
bool btree_header_write(FILE *bin_file, const BTreeHeader *header);

// ==================== Página ====================

// Marca se a página foi removida
void btree_page_set_removed(BTreePage *page, char removed);
char btree_page_get_removed(const BTreePage *page);

// Ponteiro para próxima posição na pilha de removidos
void btree_page_set_next_in_stack(BTreePage *page, int next_rrn);
int btree_page_get_next_in_stack(const BTreePage *page);

// Tipo da página (folha, raiz ou intermediária)
void btree_page_set_page_type(BTreePage *page, int type);
int btree_page_get_page_type(const BTreePage *page);

// Número de chaves armazenadas
void btree_page_set_num_of_keys(BTreePage *page, int num_keys);
int btree_page_get_num_of_keys(const BTreePage *page);

// Acesso às chaves
void btree_page_set_key(BTreePage *page, int index, BTreeKey key);
BTreeKey btree_page_get_key(const BTreePage *page, int index);

// Acesso aos filhos
void btree_page_set_child_pointer(BTreePage *page, int index, int child_rrn);
int btree_page_get_child_pointer(const BTreePage *page, int index);

// Leitura e escrita de páginas no arquivo
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
