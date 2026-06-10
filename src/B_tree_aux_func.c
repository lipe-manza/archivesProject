#include <stdio.h>

#include "../headers/B_tree.h"

bool get_B_tree_page(FILE *f_arvore_B, PAGE *page, int RRN) {
  // Pula para a pagina(no) do RRN solicitado
  if (fseek(f_arvore_B, HEADER_SIZE_B_TREE + (RRN * PAGE_SIZE_B_TREE),
            SEEK_SET) != 0)
    return false;

  // Leitura da pagina
  if (fread(&page->removed, sizeof(char), 1, f_arvore_B) != 1)
    return false;

  if (fread(&page->nextInStack, sizeof(int), 1, f_arvore_B) != 1)
    return false;

  if (fread(&page->pageType, sizeof(int), 1, f_arvore_B) != 1)
    return false;

  if (fread(&page->numOfKeys, sizeof(int), 1, f_arvore_B) != 1)
    return false;

  for (int i = 0; i < MAX_KEYS_PER_PAGE_B_TREE; i++) {
    if (fread(&page->keys[i], sizeof(int), 1, f_arvore_B) != 1)
      return false;

    if (fread(&page->archivePointer[i], sizeof(int), 1, f_arvore_B) != 1)
      return false;
  }

  for (int i = 0; i < MAX_CHILDREN_B_TREE; i++) {
    if (fread(&page->childPointer[i], sizeof(int), 1, f_arvore_B) != 1)
      return false;
  }

  return true;
}

int get_archivePointer_value_from_key(FILE *f_arvore_B, int key, int RRN,
                                      int index) {
  // Verifica se o index e maior que o limite de chaves
  if (index >= MAX_CHILDREN_B_TREE)
    return -1;

  // Vai para a pagina da key
  if (fseek(f_arvore_B, HEADER_SIZE_B_TREE + (RRN * PAGE_SIZE_B_TREE),
            SEEK_SET) != 0)
    return -1;

  char status = '1';
  // verifica se esta removido caso acesso errado
  if (fread(&status, sizeof(char), 1, f_arvore_B) != 1)
    return -1;

  if (status == '0') {
    printf("erro ao tentar pegar chave em pagina removida");
    return -1;
  }

  // Pula para o lugar exato da key
  if (fseek(f_arvore_B,
            PAGE_ARCHIVE_POINTER_POSITION_B_TREE + index * index * sizeof(int),
            SEEK_CUR) != 0)
    return -1;

  // Le o valor do rrn do arquivo de dados
  int value = -1;
  if (fread(&value, sizeof(int), 1, f_arvore_B) != 1)
    return -1;

  return value;
}
// Função que retorna se achou ou nao e a suposta supost_position
// Se der erro retorna -1 no supost_position
bool find_key_in_page(FILE *f_arvore_B, int key, int RRN,
                      int *supost_position) {
  // Vai para a pagina da key
  if (fseek(f_arvore_B, HEADER_SIZE_B_TREE + (RRN * PAGE_SIZE_B_TREE),
            SEEK_SET) != 0) {
    *supost_position = -1;
    return false;
  }

  // verifica se esta removido caso acesso errado
  char status = '1';
  if (fread(&status, sizeof(char), 1, f_arvore_B) != 1) {
    *supost_position = -1;
    return false;
  }

  if (status == '0') {
    printf("erro ao tentar pegar chave em pagina removida");
    *supost_position = -1;
    return false;
  }

  // Pula para o numOfKeys para usar no for e tira o sizeof(char) devido ao
  // fread do status
  if (fseek(f_arvore_B, PAGE_NUM_OF_KEYS_POSITION_B_TREE - sizeof(char),
            SEEK_CUR) != 0) {
    *supost_position = -1;
    return false;
  }

  // Le o numOfKeys
  int numOfKeys = -1;
  if (fread(&numOfKeys, sizeof(int), 1, f_arvore_B) != 1) {
    *supost_position = -1;
    return false;
  }

  // Auxiliares
  bool found = false;
  int archivePointer = -1;
  int key_atual = -1;

  for (int i = 0; i < MAX_KEYS_PER_PAGE_B_TREE && !found; i++) {
    if (fread(&key_atual, sizeof(int), 1, f_arvore_B) != 1) {
      *supost_position = -1;
      return false;
    }

    if (fread(&archivePointer, sizeof(int), 1, f_arvore_B) != 1) {
      *supost_position = -1;
      return false;
    }

    if (i < numOfKeys) {
      if (key_atual == key) {
        *supost_position = i;
        found = true;
      } else if (!found && key_atual > key) {
        *supost_position = i;
        found = true;
      }
    }
  }

  if (!found)
    *supost_position = numOfKeys;

  return found;
}
