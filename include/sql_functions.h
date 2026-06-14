#ifndef SQLFUNCTIONS_H
#define SQLFUNCTIONS_H

#include "data_header.h"
#include "data_record.h"
#include <stdbool.h>

// Funções principais

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

// Funções auxiliares

bool search(FILE *f_bin, DataHeader *header, bool *search_for,
            DataRecord *filter);
void insert_record(FILE *f_bin, DataHeader *header, DataRecord *record);
void update_loop(FILE *f_bin, DataHeader *header, bool *search_for,
                 DataRecord *filter, bool *update_fields,
                 DataRecord *updated_data);

#endif
