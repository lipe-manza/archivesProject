#ifndef BTREE_INSERT_H
#define BTREE_INSERT_H

#include "btree_header.h"
#include "btree_page.h"
#include <stdbool.h>
#include <stdio.h>

#define BTREE_PROMOTION 1
#define BTREE_NO_PROMOTION 0
#define BTREE_ERROR -1

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

#endif // BTREE_INSERT_H
