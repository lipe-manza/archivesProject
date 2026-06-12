#ifndef IO_H
#define IO_H

#include "../headers/registro.h"

FILE *open_bin(char *bin_name, char *mode);

void tornar_inconsistente(FILE *f_bin);

void print_registro_in_terminal(REG *registro);

void print_registro_in_terminal_csv(REG *registro);

void BinarioNaTela(char *arquivo);

void ScanQuoteString(char *str);

void read_new_registro_from_terminal(REG *new_registro);

void print_cabecalho(char *str);

int satoi(char *string, int val);

#endif
