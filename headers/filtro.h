#ifndef FILTRO_H
#define FILTRO_H

#include "../headers/registro.h"
#include <stdbool.h>

#define PUBLIC_FIELDS 8

// Campos do registro (índices): para a search[] e field
#define COD_ESTACAO 0
#define COD_LINHA 1
#define COD_PROX_ESTACAO 2
#define DIST_PROX_ESTACAO 3
#define COD_LINHA_INTEGRA 4
#define COD_EST_INTEGRA 5
#define NOME_ESTACAO
#define NOME_LINHA 7

int field_to_index(char *str);

void filter_build(REG *filter, bool search[]);

bool match_filter(REG *reg, bool search[], REG *filter);

#endif
