#ifndef HASHS_H
#define HASHS_H

#include <stdbool.h>

#define TABLE_SIZE 503


typedef struct node_p ND_P;
typedef struct bucket_p BU_P;
typedef struct hash_table_p HASH_P;


HASH_P *hash_table_pair();
void hash_table_pair_insert(HASH_P *hash_table, int e1, int e2);
void hash_table_pair_free(HASH_P **hash_table);
int hash_table_pair_get_count(HASH_P *hash);

typedef struct node_s ND_S;
typedef struct bucket_s BU_S;
typedef struct hash_table_s HASH_S;

HASH_S *hash_table_single();
void hash_table_single_insert(HASH_S *hash_table, int e1);
void hash_table_single_free(HASH_S **hash_table);
int hash_table_single_get_count(HASH_S *hash);

#endif
