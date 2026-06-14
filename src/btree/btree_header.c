#include "../../include/btree.h"
#include <stdlib.h>
#include <string.h>

// Definição real da estrutura do cabeçalho da Árvore-B
// Fica restrita a este arquivo para manter encapsulamento
// Os nomes seguem a especificação do trabalho da disciplina
struct btree_header_st {
  char status; // '0' = inconsistente, '1' = consistente
  int noRaiz;  // RRN do nó raiz. -1 se vazia
  int topo;    // RRN do topo da pilha de removidos. -1 se vazia
  int proxRRN; // Próximo RRN disponível para criação de nó
  int nroNos;  // Número total de nós (páginas) na árvore
};

BTreeHeader *btree_header_create(void) {
  BTreeHeader *new_header = (BTreeHeader *)malloc(sizeof(BTreeHeader));
  if (new_header == NULL) {
    return NULL; // Falha na alocação
  }

  // Inicialização padrão conforme especificação
  new_header->status = '0';
  new_header->noRaiz = -1;
  new_header->topo = -1;
  new_header->proxRRN = 0;
  new_header->nroNos = 0;

  return new_header;
}

void btree_header_destroy(BTreeHeader **header) {
  if (header != NULL && *header != NULL) {
    free(*header);
    *header = NULL; // Evita ponteiro pendurado
  }
}

// ==================== Getters e Setters ====================

void btree_header_set_status(BTreeHeader *header, char status) {
  if (header != NULL)
    header->status = status;
}

char btree_header_get_status(const BTreeHeader *header) {
  return (header != NULL) ? header->status : '0';
}

void btree_header_set_root_node(BTreeHeader *header, int root_node) {
  if (header != NULL)
    header->noRaiz = root_node;
}

int btree_header_get_root_node(const BTreeHeader *header) {
  return (header != NULL) ? header->noRaiz : -1;
}

void btree_header_set_top_of_stack(BTreeHeader *header, int top_of_stack) {
  if (header != NULL)
    header->topo = top_of_stack;
}

int btree_header_get_top_of_stack(const BTreeHeader *header) {
  return (header != NULL) ? header->topo : -1;
}

void btree_header_set_next_rrn(BTreeHeader *header, int next_rrn) {
  if (header != NULL)
    header->proxRRN = next_rrn;
}

int btree_header_get_next_rrn(const BTreeHeader *header) {
  return (header != NULL) ? header->proxRRN : 0;
}

void btree_header_set_node_count(BTreeHeader *header, int node_count) {
  if (header != NULL)
    header->nroNos = node_count;
}

int btree_header_get_node_count(const BTreeHeader *header) {
  return (header != NULL) ? header->nroNos : 0;
}

// ==================== Leitura e Escrita em Disco ====================

bool btree_header_read(FILE *bin_file, BTreeHeader *header) {
  if (bin_file == NULL || header == NULL) {
    return false;
  }

  // Posiciona no início do arquivo para leitura do cabeçalho
  if (fseek(bin_file, 0, SEEK_SET) != 0) {
    return false;
  }

  // Leitura sequencial dos campos do cabeçalho
  if (fread(&header->status, sizeof(char), 1, bin_file) != 1)
    return false;
  if (fread(&header->noRaiz, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fread(&header->topo, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fread(&header->proxRRN, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fread(&header->nroNos, sizeof(int), 1, bin_file) != 1)
    return false;

  return true;
}

bool btree_header_write(FILE *bin_file, const BTreeHeader *header) {
  if (bin_file == NULL || header == NULL) {
    return false;
  }

  // Posiciona no início do arquivo para escrita do cabeçalho
  if (fseek(bin_file, 0, SEEK_SET) != 0) {
    return false;
  }

  // Escrita sequencial dos campos do cabeçalho
  if (fwrite(&header->status, sizeof(char), 1, bin_file) != 1)
    return false;
  if (fwrite(&header->noRaiz, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fwrite(&header->topo, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fwrite(&header->proxRRN, sizeof(int), 1, bin_file) != 1)
    return false;
  if (fwrite(&header->nroNos, sizeof(int), 1, bin_file) != 1)
    return false;

  // Garante persistência imediata no disco
  fflush(bin_file);

  return true;
}
