#ifndef DATA_RECORD_H
#define DATA_RECORD_H

#include <stdbool.h>
#include <stdio.h>

#define RECORD_SIZE 80

typedef struct {
  char removido;
  int proximo;
  int codEstacao;
  int codLinha;
  int codProxEstacao;
  int distProxEstacao;
  int codLinhaIntegra;
  int codEstIntegra;
  int tamNomeEstacao;
  char nomeEstacao[51];
  int tamNomeLinha;
  char nomeLinha[51];
} DataRecord;

// ==================== Leitura e Escrita em Disco ====================

// Lê um registro do arquivo binário na posição atual
// Trata automaticamente o lixo ('$') no final do registro
bool data_record_read(FILE *bin_file, DataRecord *record);

// Escreve um registro no arquivo binário preenchendo até 80 bytes
bool data_record_write(FILE *bin_file, const DataRecord *record);

// Atualiza um registro em um RRN específico com campos selecionados
bool data_record_update(FILE *bin_file, int RRN, bool fields_to_update[],
                        const DataRecord *updated_data);

#endif
