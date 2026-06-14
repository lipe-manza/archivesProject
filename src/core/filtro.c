#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../../include/IO.h"
#include "../../include/filtro.h"

int field_to_index(char *str) {
  char *fields[] = {"codEstacao",      "codLinha",        "codProxEstacao",
                    "distProxEstacao", "codLinhaIntegra", "codEstIntegra",
                    "nomeEstacao",     "nomeLinha"};

  for (int i = 0; i < PUBLIC_FIELDS; i++) {
    if (strcmp(str, fields[i]) == 0)
      return i;
  }

  // Retorna -1 para indicar campo inválido
  return -1;
}

// Seta os valores correspondentes no objeto DataRecord via setters
void set_filter_field(DataRecord *filter, int field, char *field_val) {
  switch (field) {
  case COD_ESTACAO:
    data_record_set_codEstacao(filter, safe_atoi(field_val, -1));
    break;
  case COD_LINHA:
    data_record_set_codLinha(filter, safe_atoi(field_val, -1));
    break;
  case COD_PROX_ESTACAO:
    data_record_set_codProxEstacao(filter, safe_atoi(field_val, -1));
    break;
  case DIST_PROX_ESTACAO:
    data_record_set_distProxEstacao(filter, safe_atoi(field_val, -1));
    break;
  case COD_LINHA_INTEGRA:
    data_record_set_codLinhaIntegra(filter, safe_atoi(field_val, -1));
    break;
  case COD_EST_INTEGRA:
    data_record_set_codEstIntegra(filter, safe_atoi(field_val, -1));
    break;
  case NOME_ESTACAO:
    // O setter já calcula o tamanho da string
    data_record_set_nomeEstacao(filter, field_val);
    break;
  case NOME_LINHA:
    // O setter já calcula o tamanho da string
    data_record_set_nomeLinha(filter, field_val);
    break;
  }
}

// Constrói um vetor que indica quais campos devem ser conferidos e um registro
// que contém os valores a serem conferidos
void filter_build(DataRecord *filter, bool search[]) {
  int num_fields = 0;
  if (scanf(" %d", &num_fields) != 1)
    return;

  // Inicializa a marcação de campos a serem pesquisados como falsa
  memset(search, false, PUBLIC_FIELDS * sizeof(bool));

  for (int j = 0; j < num_fields; j++) {
    char field[41];
    if (scanf(" %s", field) != 1) {
      printf("Falha na leitura do campo.\n");
      return;
    }

    int field_idx = field_to_index(field);

    if (field_idx == -1) {
      printf("Campo não existente.\n");
      return;
    }

    // Marca que o campo será usado na pesquisa
    search[field_idx] = true;

    char field_val[51];
    memset(field_val, '\0', sizeof(field_val));

    // Lê o valor (entre aspas ou não) do console
    ScanQuoteString(field_val);

    set_filter_field(filter, field_idx, field_val);
  }
}

// Verifica se um registro passa por um filtro
bool match_filter(const DataRecord *reg, bool search[],
                  const DataRecord *filter) {
  for (int i = 0; i < PUBLIC_FIELDS; i++) {
    if (!search[i])
      continue;

    switch (i) {
    case COD_ESTACAO:
      if (data_record_get_codEstacao(reg) != data_record_get_codEstacao(filter))
        return false;
      break;
    case COD_LINHA:
      if (data_record_get_codLinha(reg) != data_record_get_codLinha(filter))
        return false;
      break;
    case COD_PROX_ESTACAO:
      if (data_record_get_codProxEstacao(reg) !=
          data_record_get_codProxEstacao(filter))
        return false;
      break;
    case DIST_PROX_ESTACAO:
      if (data_record_get_distProxEstacao(reg) !=
          data_record_get_distProxEstacao(filter))
        return false;
      break;
    case COD_LINHA_INTEGRA:
      if (data_record_get_codLinhaIntegra(reg) !=
          data_record_get_codLinhaIntegra(filter))
        return false;
      break;
    case COD_EST_INTEGRA:
      if (data_record_get_codEstIntegra(reg) !=
          data_record_get_codEstIntegra(filter))
        return false;
      break;
    case NOME_ESTACAO:
      if (strcmp(data_record_get_nomeEstacao(reg),
                 data_record_get_nomeEstacao(filter)) != 0)
        return false;
      break;
    case NOME_LINHA:
      if (strcmp(data_record_get_nomeLinha(reg),
                 data_record_get_nomeLinha(filter)) != 0)
        return false;
      break;
    }
  }

  return true;
}

// Verifica se o campo 'codEstacao' bate com o filtro
bool match_codEstacao(const DataRecord *reg, bool search[],
                      const DataRecord *filter) {

  if (search[COD_ESTACAO] &&
      data_record_get_codEstacao(reg) == data_record_get_codEstacao(filter))
    return true;
  return false;
}
