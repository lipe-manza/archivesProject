#ifndef SQLFUNCTIONS_H
#define SQLFUNCTIONS_H

#include "registro.h"
#include <stdbool.h>

void create_table();
void select_from();
void select_from_where();
void delete_from_where();
void insert_into();
void update_set_where();
void create_index();
void select_from_where_ab();
void delete_from_where_ab();
void insert_into_ab();

bool search(FILE *f_bin, CAB *cabecalho, bool *search_for, REG *filter);
void read_insert_reg(FILE **f_bin, CAB *cabecalho, REG *registro);
void update_loop(FILE *f_bin, CAB cabecalho, bool *search, REG *filter,
                 bool *update, REG *updated);

#endif
