#ifndef TOOLS_H
#define TOOLS_H

#include "data_header.h"
#include <stdbool.h>
#include <stdio.h>

// Recalcula o número de estações únicas e pares de estações varrendo o
// arquivo.
bool update_statistics(FILE *f_bin, DataHeader *header);

#endif
