#ifndef BTREE_HEADER_H
#define BTREE_HEADER_H

#include <stdbool.h>
#include <stdio.h>

#define BTREE_HEADER_SIZE 17

/**
 * @brief Tipo Abstrato de Dados opaco que representa o registro de cabeçalho
 * do arquivo de índice da Árvore-B.
 */
typedef struct btree_header_st BTreeHeader;

/**
 * @brief Instancia dinamicamente um novo registro de cabeçalho da Árvore-B
 * com os valores padrão para um arquivo vazio (inconsistente por padrão).
 * @return Ponteiro para o BTreeHeader alocado na heap, ou NULL em caso de
 * falha.
 */
BTreeHeader *btree_header_create(void);

/**
 * @brief Libera a memória alocada para o registro de cabeçalho da Árvore-B e
 * anula o ponteiro.
 * @param header Ponteiro duplo para o cabeçalho para evitar dangling pointers.
 */
void btree_header_destroy(BTreeHeader **header);

// ==================== Getters & Setters ====================

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

// ==================== I/O em Disco ====================

/**
 * @brief Lê o registro de cabeçalho diretamente do início (byte offset 0) do
 * arquivo binário de índice.
 * @param bin_file Ponteiro para o arquivo binário aberto para leitura.
 * @param header Estrutura previamente alocada onde os dados serão armazenados.
 * @return true se a leitura dos 17 bytes foi bem-sucedida, false caso
 * contrário.
 */
bool btree_header_read(FILE *bin_file, BTreeHeader *header);

/**
 * @brief Escreve o registro de cabeçalho no início do arquivo binário de
 * índice. Força a consistência posicional indo para o byte offset 0 antes de
 * escrever.
 * @param bin_file Ponteiro para o arquivo binário aberto para escrita.
 * @param header Estrutura com os dados a serem escritos.
 * @return true se a escrita dos 17 bytes foi bem-sucedida, false caso
 * contrário.
 */
bool btree_header_write(FILE *bin_file, const BTreeHeader *header);

#endif // BTREE_HEADER_H
