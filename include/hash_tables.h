#ifndef HASH_H
#define HASH_H

#define MAX_NOME 41

// Tipos Opacos
typedef struct hash_estacao HashEstacao;
typedef struct hash_par HashPar;

// Interface para Estações (Strings)
HashEstacao* criar_hash_est();
int inserir_est(HashEstacao *ht, const char *nome);
int get_nro_estacoes(HashEstacao *ht);
void destruir_hash_est(HashEstacao *ht);

// Interface para Pares (Inteiros)
HashPar* criar_hash_par();
int inserir_par(HashPar *ht, int c1, int c2);
int get_nro_pares(HashPar *ht);
void destruir_hash_par(HashPar *ht);

#endif
