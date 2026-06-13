#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../include/data_header.h"
#include "../../include/data_record.h"
#include "../../include/hash_tables.h"

/**
 * @brief Recalcula o número de estações únicas e pares de estações varrendo
 * todo o arquivo binário. Atualiza os valores diretamente no objeto DataHeader
 * fornecido em memória.
 */
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

  int reg_count = data_header_get_proxRRN(header);
  DataRecord *record = data_record_create();
  if (record == NULL) {
    free_hash_estacao(hash_single);
    free_hash_par(hash_pair);
    return false;
  }

  // Pula o cabeçalho físico
  fseek(f_bin, HEADER_SIZE, SEEK_SET);

  for (int rrn = 0; rrn < reg_count; rrn++) {
    // A função data_record_read avança o ponteiro automaticamente e lida com o
    // lixo físico
    if (!data_record_read(f_bin, record))
      break;

    if (data_record_get_removido(record) == '1')
      continue;

    inserir_estacao(hash_single, data_record_get_nomeEstacao(record));
    inserir_par(hash_pair, data_record_get_codEstacao(record),
                data_record_get_codProxEstacao(record));
  }

  // Atualiza as contagens diretamente no cabeçalho em memória (a escrita pro
  // disco é feita por quem chamou)
  data_header_set_nroEstacoes(header, get_nro_estacoes(hash_single));
  data_header_set_nroParesEstacoes(header, get_nro_pares(hash_pair));

  data_record_destroy(&record);
  free_hash_estacao(hash_single);
  free_hash_par(hash_pair);

  return true;
}
