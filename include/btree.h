#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>
#include <stdio.h>

// ==================== Constantes e Macros ====================

// Dimensões físicas e lógicas da Árvore-B
#define BTREE_ORDER 4
#define BTREE_MAX_KEYS 3
#define BTREE_MAX_CHILDREN 4

#define BTREE_HEADER_SIZE 17
#define BTREE_PAGE_SIZE 53

// Tipos de Página
#define PAGE_TYPE_LEAF -1
#define PAGE_TYPE_ROOT 0
#define PAGE_TYPE_MID 1

// Retornos de Operações
#define BTREE_PROMOTION 1
#define BTREE_NO_PROMOTION 0
#define BTREE_ERROR -1
#define BTREE_NOT_FOUND -1

// ==================== Tipos e Estruturas ====================

/**
 * @brief DTO (Data Transfer Object) público para facilitar o transporte
 * de uma chave e sua referência sem quebrar o encapsulamento do nó.
 */
typedef struct {
  int C;  // Chave de busca (codEstacao)
  int Pr; // Ponteiro de referência (byte offset no arquivo de dados)
} BTreeKey;

/**
 * @brief Tipo Abstrato de Dados opaco que representa o registro de cabeçalho
 * do arquivo de índice da Árvore-B.
 */
typedef struct btree_header_st BTreeHeader;

/**
 * @brief Tipo Abstrato de Dados opaco que representa um nó (página) da
 * Árvore-B.
 */
typedef struct btree_page_st BTreePage;

// ==================== Gerenciamento de Memória ====================

/**
 * @brief Instancia dinamicamente um novo registro de cabeçalho da Árvore-B.
 * @return Ponteiro para o BTreeHeader alocado na heap, ou NULL em caso de
 * falha.
 */
BTreeHeader *btree_header_create(void);

/**
 * @brief Libera a memória alocada para o registro de cabeçalho e anula o
 * ponteiro.
 * @param header Ponteiro duplo para o cabeçalho.
 */
void btree_header_destroy(BTreeHeader **header);

/**
 * @brief Instancia dinamicamente uma nova página da Árvore-B com valores nulos.
 * @return Ponteiro para a BTreePage alocada, ou NULL em caso de falha.
 */
BTreePage *btree_page_create(void);

/**
 * @brief Libera a memória alocada para a página e anula o ponteiro.
 * @param page Ponteiro duplo para a página.
 */
void btree_page_destroy(BTreePage **page);

// ==================== Interface do Cabeçalho ====================

void btree_header_set_status(BTreeHeader *header, char status);
char btree_header_get_status(const BTreeHeader *header);

void btree_header_set_root_node(BTreeHeader *header, int root_node);
int btree_header_get_root_node(const BTreeHeader *header);

void btree_header_set_top_of_stack(BTreeHeader *header, int top_of_stack);
int btree_header_get_top_of_stack(const BTreeHeader *header);

void btree_header_set_next_rrn(BTreeHeader *header, int next_rrn);
int btree_header_get_next_rrn(const BTreeHeader *header);

void btree_header_set_node_count(BTreeHeader *header, int node_count);
int btree_header_get_node_count(const BTreeHeader *header);

bool btree_header_read(FILE *bin_file, BTreeHeader *header);
bool btree_header_write(FILE *bin_file, const BTreeHeader *header);

// ==================== Interface da Página ====================

void btree_page_set_removed(BTreePage *page, char removed);
char btree_page_get_removed(const BTreePage *page);

void btree_page_set_next_in_stack(BTreePage *page, int next_rrn);
int btree_page_get_next_in_stack(const BTreePage *page);

void btree_page_set_page_type(BTreePage *page, int type);
int btree_page_get_page_type(const BTreePage *page);

void btree_page_set_num_of_keys(BTreePage *page, int num_keys);
int btree_page_get_num_of_keys(const BTreePage *page);

void btree_page_set_key(BTreePage *page, int index, BTreeKey key);
BTreeKey btree_page_get_key(const BTreePage *page, int index);

void btree_page_set_child_pointer(BTreePage *page, int index, int child_rrn);
int btree_page_get_child_pointer(const BTreePage *page, int index);

bool btree_page_read(FILE *bin_file, BTreePage *page, int rrn);
bool btree_page_write(FILE *bin_file, const BTreePage *page, int rrn);

// ==================== Operações Principais (CRUD) ====================

/**
 * @brief Insere uma nova chave no arquivo de índice Árvore-B.
 * Gerencia automaticamente a busca pela folha correta, o particionamento
 * (split) e a criação de novas raízes, se necessário.
 * @param bin_file Ponteiro para o arquivo binário de índice.
 * @param header Cabeçalho carregado na memória.
 * @param key Chave (codEstacao) e referência (byte offset) a ser inserida.
 * @return true se a inserção ocorreu com sucesso, false em caso de erro ou
 * chave duplicada.
 */
bool btree_insert_key(FILE *bin_file, BTreeHeader *header, BTreeKey key);

/**
 * @brief Realiza a busca de uma chave (codEstacao) na Árvore-B.
 * Desce iterativamente pela árvore guiada pelos ponteiros de subárvore.
 * @param bin_file Ponteiro para o arquivo binário de índice aberto para
 * leitura.
 * @param header Ponteiro para o cabeçalho da Árvore-B carregado na memória.
 * @param search_key O valor da chave (codEstacao) a ser buscada.
 * @return O byte offset (Pr) do registro no arquivo de dados se encontrado,
 * ou BTREE_NOT_FOUND (-1) se a chave não existir na árvore.
 */
int btree_search_key(FILE *bin_file, BTreeHeader *header, int search_key);

/**
 * @brief Remove uma chave do arquivo de índice Árvore-B.
 * Trata automaticamente o underflow através de redistribuição (empréstimos),
 * concatenações (merge) e atualizações da raiz, garantindo o descarte
 * correto de páginas para a pilha de removidos.
 * @param bin_file Ponteiro para o arquivo binário de índice aberto para
 * leitura/escrita.
 * @param header Ponteiro para o cabeçalho da Árvore-B carregado na memória.
 * @param key_to_delete O valor da chave (codEstacao) a ser removida.
 * @return true se a chave foi encontrada e removida com sucesso,
 * false caso a chave não exista na árvore ou ocorra um erro.
 */
bool btree_delete_key(FILE *bin_file, BTreeHeader *header, int key_to_delete);

#endif // BTREE_H
