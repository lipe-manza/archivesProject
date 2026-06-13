#ifndef BTREE_PAGE_H
#define BTREE_PAGE_H

#include "btree_header.h"
#include <stdbool.h>
#include <stdio.h>

#define BTREE_PAGE_SIZE 53
#define BTREE_ORDER 4
#define BTREE_MAX_KEYS 3
#define BTREE_MAX_CHILDREN 4

#define PAGE_TYPE_LEAF -1
#define PAGE_TYPE_ROOT 0
#define PAGE_TYPE_MID 1

/**
 * @brief DTO (Data Transfer Object) público para facilitar o transporte
 * de uma chave e sua referência sem quebrar o encapsulamento do nó.
 */
typedef struct {
  int C;  // Chave de busca (codEstacao)
  int Pr; // Ponteiro de referência (byte offset no arquivo de dados)
} BTreeKey;

/**
 * @brief Tipo Abstrato de Dados opaco que representa um nó (página) da
 * Árvore-B.
 */
typedef struct btree_page_st BTreePage;

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

// ==================== Getters & Setters ====================

void btree_page_set_removed(BTreePage *page, char removed);
char btree_page_get_removed(const BTreePage *page);

void btree_page_set_next_in_stack(BTreePage *page, int next_rrn);
int btree_page_get_next_in_stack(const BTreePage *page);

void btree_page_set_page_type(BTreePage *page, int type);
int btree_page_get_page_type(const BTreePage *page);

void btree_page_set_num_of_keys(BTreePage *page, int num_keys);
int btree_page_get_num_of_keys(const BTreePage *page);

/**
 * @brief Define uma chave em um índice específico da página (0 a 2).
 */
void btree_page_set_key(BTreePage *page, int index, BTreeKey key);

/**
 * @brief Retorna uma chave de um índice específico da página.
 */
BTreeKey btree_page_get_key(const BTreePage *page, int index);

/**
 * @brief Define um ponteiro para subárvore em um índice específico (0 a 3).
 */
void btree_page_set_child_pointer(BTreePage *page, int index, int child_rrn);

/**
 * @brief Retorna o RRN de um filho em um índice específico.
 */
int btree_page_get_child_pointer(const BTreePage *page, int index);

// ==================== I/O em Disco ====================

/**
 * @brief Lê uma página do arquivo binário baseada no seu RRN.
 * Calcula automaticamente o byte offset correto considerando o cabeçalho.
 * @param bin_file Ponteiro para o arquivo binário.
 * @param page Estrutura que receberá os dados.
 * @param rrn Relative Record Number da página a ser lida.
 * @return true se a leitura foi bem-sucedida.
 */
bool btree_page_read(FILE *bin_file, BTreePage *page, int rrn);

/**
 * @brief Escreve uma página no arquivo binário na posição do seu RRN.
 * @param bin_file Ponteiro para o arquivo binário.
 * @param page Página a ser gravada.
 * @param rrn Relative Record Number indicando a posição de destino.
 * @return true se a escrita ocorreu com sucesso.
 */
bool btree_page_write(FILE *bin_file, const BTreePage *page, int rrn);

#endif // BTREE_PAGE_H
