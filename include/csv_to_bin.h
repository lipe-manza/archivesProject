#ifndef CSVTOBIN_H
#define CSVTOBIN_H

#include <stdbool.h>
#include <stdio.h>

typedef struct registro REG;

bool csv_to_bin(char *csv_name, char *bin_name);


#endif
