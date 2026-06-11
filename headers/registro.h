#ifndef REG_H
#define REG_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_REGISTRO 80
#define TAM_CABECALHO 17
#define POS_PROX_RRN 5

typedef struct cabecalho {
  char status;
  int topo;
  int proxRRN;
  int nroEstacoes;
  int nroParesEstacoes;
} CABECALHO;

typedef struct registro {
  char removido; // '1' para removido e '0' para nao removido
  int proximo;
  int codEstacao; // Não pode ser nulo
  int codLinha;
  int codProxEstacao;
  int distProxEstacao;
  int codLinhaIntegra;
  int codEstIntegra;
  int tamNomeEstacao;   // Se for 0 não escrever o nomeEstacao
  char nomeEstacao[51]; // Não pode ser nulo
  int tamNomeLinha;
  char nomeLinha[51];
} REG;

bool read_from_bin(FILE *p_bin, REG *reg);
void write_in_bin(FILE *p_bin, REG *reg);
void update_bin(FILE *f_bin, int RRN, REG *registro, bool atualizar[],
                REG *atualizado);
bool atualizar_estacoes(FILE *p_bin);

#endif
