#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../headers/registro.h"

#include "../../headers/hash_tables.h"

// ---------- FUNÇÕES DE CABEÇALHO ----------

bool construir_cab(CAB *cabecalho, char status, int topo, int proxRRN,
                   int nroEstacoes, int nroParesEstacoes) {
  if (cabecalho == NULL)
    return false;

  cabecalho->status = status;
  cabecalho->topo = topo;
  cabecalho->proxRRN = proxRRN;
  cabecalho->nroEstacoes = nroEstacoes;
  cabecalho->nroParesEstacoes = nroParesEstacoes;
  return true;
}

bool read_cab_bin(FILE *f_bin, CAB *cab) {
  // Verifica se o arquivo e o cabeçalho são válidos
  if (f_bin == NULL || cab == NULL)
    return false;

  // Vai para o início da página, onde está o cabeçalho
  fseek(f_bin, 0, SEEK_SET);

  if (fread(&cab->status, sizeof(cab->status), 1, f_bin) != 1)
    return false;
  if (fread(&cab->topo, sizeof(cab->topo), 1, f_bin) != 1)
    return false;
  if (fread(&cab->proxRRN, sizeof(cab->proxRRN), 1, f_bin) != 1)
    return false;
  if (fread(&cab->nroEstacoes, sizeof(cab->nroEstacoes), 1, f_bin) != 1)
    return false;
  if (fread(&cab->nroParesEstacoes, sizeof(cab->nroParesEstacoes), 1, f_bin) !=
      1)
    return false;

  return true;
}

void write_cab_bin(FILE *f_bin, CAB *cab) {
  // Verifica se o arquivo e o cabeçalho são válidos
  if (f_bin == NULL || cab == NULL)
    return;

  // Vai para o início da página, onde está o cabeçalho
  fseek(f_bin, 0, SEEK_SET);

  fwrite(&cab->status, sizeof(cab->status), 1, f_bin);
  fwrite(&cab->topo, sizeof(cab->topo), 1, f_bin);
  fwrite(&cab->proxRRN, sizeof(cab->proxRRN), 1, f_bin);
  fwrite(&cab->nroEstacoes, sizeof(cab->nroEstacoes), 1, f_bin);
  fwrite(&cab->nroParesEstacoes, sizeof(cab->nroParesEstacoes), 1, f_bin);
}

// ---------- FUNÇÕES DE REGISTRO ----------

bool read_reg_bin(FILE *f_bin, REG *reg) {
  // Verifica se o arquivo e o registro são válidos
  if (f_bin == NULL || reg == NULL)
    return false;

  long pos_inicial = ftell(f_bin);

  if (fread(&reg->removido, sizeof(reg->removido), 1, f_bin) != 1)
    return false;
  // Caso o registro esteja marcado como removido, pular
  if (reg->removido == '1') {
    fseek(f_bin, TAM_REGISTRO - 1, SEEK_CUR);
    return true;
  }
  if (fread(&reg->proximo, sizeof(reg->proximo), 1, f_bin) != 1)
    return false;
  if (fread(&reg->codEstacao, sizeof(reg->codEstacao), 1, f_bin) != 1)
    return false;
  if (fread(&reg->codLinha, sizeof(reg->codLinha), 1, f_bin) != 1)
    return false;
  if (fread(&reg->codProxEstacao, sizeof(reg->codProxEstacao), 1, f_bin) != 1)
    return false;
  if (fread(&reg->distProxEstacao, sizeof(reg->distProxEstacao), 1, f_bin) != 1)
    return false;
  if (fread(&reg->codLinhaIntegra, sizeof(reg->codLinhaIntegra), 1, f_bin) != 1)
    return false;
  if (fread(&reg->codEstIntegra, sizeof(reg->codEstIntegra), 1, f_bin) != 1)
    return false;

  if (fread(&reg->tamNomeEstacao, sizeof(reg->tamNomeEstacao), 1, f_bin) != 1)
    return false;
  if (reg->tamNomeEstacao > 0) {
    if (fread(reg->nomeEstacao, sizeof(char), reg->tamNomeEstacao, f_bin) !=
        (size_t)reg->tamNomeEstacao)
      return false;
    reg->nomeEstacao[reg->tamNomeEstacao] = '\0'; // coloca \0 na string
  } else
    reg->nomeEstacao[0] = '\0';

  if (fread(&reg->tamNomeLinha, sizeof(reg->tamNomeLinha), 1, f_bin) != 1)
    return false;
  if (reg->tamNomeLinha > 0) {
    if (fread(reg->nomeLinha, sizeof(char), reg->tamNomeLinha, f_bin) !=
        (size_t)reg->tamNomeLinha)
      return false;
    reg->nomeLinha[reg->tamNomeLinha] = '\0'; // coloca \0 na string
  } else
    reg->nomeLinha[0] = '\0';

  long bytes_lidos = ftell(f_bin) - pos_inicial;

  long bytes_restantes = TAM_REGISTRO - bytes_lidos;

  if (bytes_restantes > 0) {
    char lixo[bytes_restantes];
    if (fread(lixo, sizeof(char), bytes_restantes, f_bin) !=
        (size_t)bytes_restantes) {
      return false;
    }
  }

  return true;
}

void write_in_bin(FILE *f_bin, REG *reg) {

  fwrite(&reg->removido, sizeof(reg->removido), 1, f_bin);
  fwrite(&reg->proximo, sizeof(reg->proximo), 1, f_bin);
  fwrite(&reg->codEstacao, sizeof(reg->codEstacao), 1, f_bin);
  fwrite(&reg->codLinha, sizeof(reg->codLinha), 1, f_bin);
  fwrite(&reg->codProxEstacao, sizeof(reg->codProxEstacao), 1, f_bin);
  fwrite(&reg->distProxEstacao, sizeof(reg->distProxEstacao), 1, f_bin);
  fwrite(&reg->codLinhaIntegra, sizeof(reg->codLinhaIntegra), 1, f_bin);
  fwrite(&reg->codEstIntegra, sizeof(reg->codEstIntegra), 1, f_bin);

  fwrite(&reg->tamNomeEstacao, sizeof(reg->tamNomeEstacao), 1, f_bin);
  if (reg->tamNomeEstacao > 0)
    fwrite(reg->nomeEstacao, sizeof(char), reg->tamNomeEstacao, f_bin);

  fwrite(&reg->tamNomeLinha, sizeof(reg->tamNomeLinha), 1, f_bin);
  if (reg->tamNomeLinha > 0)
    fwrite(reg->nomeLinha, sizeof(char), reg->tamNomeLinha, f_bin);

  // Escreve os bytes de lixo no final do registro para completar os
  // TAM_REGISTRO bytes do registro
  char lixo = '$';
  int bytes_usados = 37 + reg->tamNomeEstacao + reg->tamNomeLinha;
  int lixo_size = TAM_REGISTRO - bytes_usados;

  if (lixo_size > 0) {
    char buffer_lixo[41];
    memset(buffer_lixo, lixo, lixo_size);
    fwrite(buffer_lixo, sizeof(char), lixo_size, f_bin);
  }
}

bool atualizar_registro(FILE *f_bin, int RRN, REG *registro, bool atualizar[],
                        REG *atualizado) {
  // Verifica se o arquivo e o registro são válidos
  if (f_bin == NULL || registro == NULL)
    return false;

  // Atualiza os campos do registro de acordo com o array atualizar
  if (atualizar[0])
    registro->codEstacao = atualizado->codEstacao;
  if (atualizar[1])
    registro->codLinha = atualizado->codLinha;
  if (atualizar[2])
    registro->codProxEstacao = atualizado->codProxEstacao;
  if (atualizar[3])
    registro->distProxEstacao = atualizado->distProxEstacao;
  if (atualizar[4])
    registro->codLinhaIntegra = atualizado->codLinhaIntegra;
  if (atualizar[5])
    registro->codEstIntegra = atualizado->codEstIntegra;

  if (atualizar[6]) {
    registro->tamNomeEstacao = atualizado->tamNomeEstacao;
    strcpy(registro->nomeEstacao, atualizado->nomeEstacao);
  }
  if (atualizar[7]) {
    registro->tamNomeLinha = atualizado->tamNomeLinha;
    strcpy(registro->nomeLinha, atualizado->nomeLinha);
  }

  // Sobrescreve o registro atualizado no arquivo .bin
  fseek(f_bin, TAM_CABECALHO + (RRN * TAM_REGISTRO), SEEK_SET);
  write_in_bin(f_bin, registro);
  return true;
}

bool atualizar_estacoes(FILE *f_bin) {
  // Cria as hashtables para contar as estações e pares de estações únicas
  HashEstacao *hash_single = criar_hash_estacao();
  HashPar *hash_pair = criar_hash_par();

  // Encerra o programa em caso de falha de alocação de alguma das hashtables
  if (hash_single == NULL || hash_pair == NULL) {
    free(hash_single);
    free(hash_pair);
    printf("Falha no processamento do arquivo\n");
    return false;
  }

  // Vai para o campo proxRRN do registro de cabeçalho para ler quantos
  // registros existem
  int reg_count = 0;
  fseek(f_bin, 5, SEEK_SET);
  if (fread(&reg_count, sizeof(int), 1, f_bin) != 1) {
    printf("Falha no processamento do arquivo.\n");
    return false;
  }

  // Struct registro auxiliar para ler o .bin
  REG registro;

  // Itera por todos os registros do arquivo .bin e insere as estações e os
  // pares de estações nas hashtables
  for (int RRN = 0; RRN < reg_count; RRN++) {
    // Vai para o byteoffset do registro atual
    fseek(f_bin, RRN * TAM_REGISTRO + TAM_CABECALHO, SEEK_SET);

    // Lê o registro do .bin para a struct registro
    read_from_bin(f_bin, &registro);

    // Se o registro está removido ele não é levando em conta
    if (registro.removido == '1')
      continue;

    inserir_estacao(hash_single, registro.nomeEstacao);

    inserir_par(hash_pair, registro.codEstacao, registro.codProxEstacao);
  }

  int nroEstacoes = get_nro_estacoes(hash_single);
  int nroParesEstacao = get_nro_pares(hash_pair);

  // Aponta para o campo número de estações do registro de cabeçalho e escreve
  // o número de estações e o número de pares
  fseek(f_bin, 9, SEEK_SET);
  fwrite(&nroEstacoes, sizeof(int), 1, f_bin);
  fwrite(&nroParesEstacao, sizeof(int), 1, f_bin);

  // Dar free nas hashtables
  free_hash_estacao(hash_single);
  free_hash_par(hash_pair);

  return true;
}
