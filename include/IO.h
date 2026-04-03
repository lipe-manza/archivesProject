#ifndef IO_H
#define IO_H

#include "../include/registro.h"

void read_from_bin(FILE *p_bin, REG *reg);
void write_in_bin(FILE *p_bin, REG *reg);
void print_registro_in_terminal(REG *registro);

void BinarioNaTela(char *arquivo);
void ScanQuoteString(char *str);


#endif
