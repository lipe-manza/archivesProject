#ifndef FILTRO_H
#define FILTRO_H

#include "registro.h"
#include <stdbool.h>
#define PUBLIC_FIELDS 8

/*
Campos do registro (índices): para a search[] e field
[0]  codEstacao
[1]  codLinha
[2]  codProxEstacao
[3]  distProxEstacao
[4]  codLinhaIntegra
[5]  codEstIntegra
[6]  nomeEstacao
[7]  nomeLinha
*/

int field_to_index(char *str);

void filter_build(REG *filter, bool search[]);

bool match_filter(REG *reg, bool search[], REG *filter);

#endif
