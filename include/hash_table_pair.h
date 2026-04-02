#ifndef PAIR_H
#define PAIR_H

#include <stdbool.h>

#define TABLE_SIZE 503


typedef struct node ND;
typedef struct bucket BU;
typedef struct hash_table HASH_P;


HASH_P *hash_table_pair();
void hash_table_pair_insert(HASH_P *hash_table, int e1, int e2);
void hash_table_pair_free(HASH_P **hash_table);
int hash_table_pair_get_count(HASH_P *hash);

#endif
