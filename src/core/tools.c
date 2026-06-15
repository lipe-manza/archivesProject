#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include "../../include/hash_tables.h"

// Recalcula o número de estações únicas e pares de estações varrendo
// todo o arquivo binário. Atualiza os valores diretamente no objeto DataHeader
// fornecido em memória.
bool update_statistics(FILE *f_bin, DataHeader *header) {
  if (f_bin == NULL || header == NULL)
    return false;

  HashEstacao *hash_single = criar_hash_estacao();
  HashPar *hash_pair = criar_hash_par();

  if (hash_single == NULL || hash_pair == NULL) {
    free_hash_estacao(hash_single); // free lida internamente se for nulo
    free_hash_par(hash_pair);
    printf("Falha no processamento do arquivo.\n");
    return false;
  }

  int reg_count = header->proxRRN;
  DataRecord record;

  // Pula o cabeçalho físico
  fseek(f_bin, HEADER_SIZE, SEEK_SET);

  for (int rrn = 0; rrn < reg_count; rrn++) {
    // A função data_record_read avança o ponteiro automaticamente e lida com o
    // lixo físico
    if (!data_record_read(f_bin, &record))
      break;

    if (record.removido == '1')
      continue;

    inserir_estacao(hash_single, record.nomeEstacao);
    inserir_par(hash_pair, record.codEstacao,
                record.codProxEstacao);
  }

  // Atualiza as contagens diretamente no cabeçalho em memória (a escrita pro
  // disco é feita por quem chamou)
  header->nroEstacoes = get_nro_estacoes(hash_single);
  header->nroParesEstacoes = get_nro_pares(hash_pair);

  free_hash_estacao(hash_single);
  free_hash_par(hash_pair);

  return true;
}
