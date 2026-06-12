#ifndef REG_H
#define REG_H

#include <stdbool.h>
#include <stdio.h>

#define TAM_CABECALHO 17
#define POS_PROX_RRN_CAB 5

typedef struct cabecalho {
  char status;
  int topo;
  int proxRRN;
  int nroEstacoes;
  int nroParesEstacoes;
} CAB;

#define TAM_REGISTRO 80
#define POS_REM_REG 0
#define POS_PROX_REG 1

#define REG_BYTE_OFFSET(RRN) TAM_CABECALHO + (TAM_REGISTRO * RRN)

typedef struct registro {
  char removido;
  int proximo;
  int codEstacao; // Não pode ser nulo
  int codLinha;
  int codProxEstacao;
  int distProxEstacao;
  int codLinhaIntegra;
  int codEstIntegra;
  int tamNomeEstacao;
  char nomeEstacao[51]; // Não pode ser nulo
  int tamNomeLinha;
  char nomeLinha[51];
} REG;

bool construir_cab(CAB *cabecalho, char status, int topo, int proxRRN,
                   int nroEstacoes, int nroParesEstacoes);
bool ler_cab_bin(FILE *f_bin, CAB *cab);
void escrever_cab_bin(FILE *f_bin, CAB *cab);

bool ler_reg_bin(FILE *f_bin, REG *reg);
void escrever_reg_bin(FILE *f_bin, REG *reg);
void atualizar_reg_bin(FILE *f_bin, int RRN, REG *registro, bool atualizar[],
                       REG *atualizado);

bool atualizar_estacoes(FILE *f_bin);

#endif
