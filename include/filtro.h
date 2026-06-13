#ifndef FILTRO_H
#define FILTRO_H

#include "data_record.h"
#include <stdbool.h>

#define PUBLIC_FIELDS 8

// Índices mapeados para o array search_for[]
#define COD_ESTACAO 0
#define COD_LINHA 1
#define COD_PROX_ESTACAO 2
#define DIST_PROX_ESTACAO 3
#define COD_LINHA_INTEGRA 4
#define COD_EST_INTEGRA 5
#define NOME_ESTACAO 6
#define NOME_LINHA 7

int field_to_index(char *str);

/**
 * @brief Lê a entrada padrão e preenche o registro de filtro e o array de
 * busca.
 */
void filter_build(DataRecord *filter, bool search[]);

/**
 * @brief Compara um registro com o filtro de pesquisa.
 * @return true se o registro corresponde ao filtro, false caso contrário.
 */
bool match_filter(const DataRecord *reg, bool search[],
                  const DataRecord *filter);

#endif
