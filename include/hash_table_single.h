#ifndef SINGLE_H
#define SINGLE_H

#include <stdbool.h>

#define TABLE_SIZE 503

typedef struct node ND;
typedef struct bucket BU;
typedef struct hash_table HASH_S;

HASH_S *hash_table_single();
void hash_table_single_insert(HASH_S *hash_table, int e1);
void hash_table_single_free(HASH_S *hash_table);
int hash_table_single_get_count(HASH_S *hash);

#endif
