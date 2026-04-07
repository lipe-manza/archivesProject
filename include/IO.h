#ifndef IO_H
#define IO_H

#include "../include/registro.h"

void print_registro_in_terminal(REG *registro);

void BinarioNaTela(char *arquivo);

void ScanQuoteString(char *str);

void read_new_registro_from_terminal(REG *new_registro);


#endif
