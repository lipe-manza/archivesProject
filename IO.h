#ifndef IO_H
#define IO_H

#include "registro.h"

void print_registro_in_terminal(REG *registro);

void print_registro_in_terminal_csv(REG *registro);

void BinarioNaTela(char *arquivo);

void ScanQuoteString(char *str);

void read_new_registro_from_terminal(REG *new_registro);

void print_cabecalho(char *str);

#endif
