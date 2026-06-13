#ifndef TOOLS_H
#define TOOLS_H

#include "data_header.h"
#include <stdbool.h>
#include <stdio.h>

/**
 * @brief Recalcula o número de estações únicas e pares de estações varrendo o
 * arquivo.
 * @param f_bin Ponteiro para o arquivo binário.
 * @param header Ponteiro para o cabeçalho em memória que será atualizado.
 * @return true se a atualização foi bem sucedida.
 */
bool update_statistics(FILE *f_bin, DataHeader *header);

#endif
