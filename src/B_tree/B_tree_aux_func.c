#include <stdio.h>

#include "../../headers/B_tree.h"

bool read_B_tree_page_from_bin(FILE *f_arvore_B, PAGE *page, int RRN) {
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

    if (fread(&page->filePointer[i], sizeof(int), 1, f_arvore_B) != 1)
      return false;
  }

  for (int i = 0; i < MAX_CHILDREN_B_TREE; i++) {
    if (fread(&page->childPointer[i], sizeof(int), 1, f_arvore_B) != 1)
      return false;
  }

  return true;
}

bool write_B_tree_page_in_bin(FILE *f_arvore_B, PAGE *page, int RRN) {
  // Pula para a pagina(no) do RRN solicitado
  if (fseek(f_arvore_B, HEADER_SIZE_B_TREE + (RRN * PAGE_SIZE_B_TREE),
            SEEK_SET) != 0)
    return false;

  // Escrita da pagina
  if (fwrite(&page->removed, sizeof(char), 1, f_arvore_B) != 1)
    return false;

  if (fwrite(&page->nextInStack, sizeof(int), 1, f_arvore_B) != 1)
    return false;

  if (fwrite(&page->pageType, sizeof(int), 1, f_arvore_B) != 1)
    return false;

  if (fwrite(&page->numOfKeys, sizeof(int), 1, f_arvore_B) != 1)
    return false;

  for (int i = 0; i < MAX_KEYS_PER_PAGE_B_TREE; i++) {
    if (fwrite(&page->keys[i], sizeof(int), 1, f_arvore_B) != 1)
      return false;

    if (fwrite(&page->filePointer[i], sizeof(int), 1, f_arvore_B) != 1)
      return false;
  }

  for (int i = 0; i < MAX_CHILDREN_B_TREE; i++) {
    if (fwrite(&page->childPointer[i], sizeof(int), 1, f_arvore_B) != 1)
      return false;
  }

  return true;
}
int get_filePointer_value_from_key(FILE *f_arvore_B, int key, int RRN,
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
            PAGE_FILE_POINTER_POSITION_B_TREE + index * index * sizeof(int),
            SEEK_CUR) != 0)
    return -1;

  // Le o valor do rrn do arquivo de dados
  int value = -1;
  if (fread(&value, sizeof(int), 1, f_arvore_B) != 1)
    return -1;

  return value;
}
