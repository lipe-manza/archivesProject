#ifndef FILTRO_H
#define FILTRO_H

#include <stdbool.h>
#include "registro.h"
#define PUBLIC_FIELDS 8

/*
Campos do registro (índices): para a pesquisa[] e op
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

void set_filtro(REG *filtro, int op, char *str);

bool match_filtro(REG *reg, bool pesquisa[], REG *filtro);


#endif
