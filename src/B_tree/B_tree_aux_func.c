#include <stdio.h>

#include "../../headers/B_tree.h"

bool read_B_tree_page_from_bin(FILE *f_arvore_B, PAGE *page, int RRN) {
  // Pula para a pagina(no) do RRN solicitado
  if (fseek(f_arvore_B, PAGE_OFFSET_B_TREE(RRN), SEEK_SET) != 0)
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
    if (fread(&page->keys[i].value, sizeof(int), 1, f_arvore_B) != 1)
      return false;

    if (fread(&page->keys[i].byteOffset, sizeof(int), 1, f_arvore_B) != 1)
      return false;
  }

  for (int i = 0; i < MAX_CHILDREN_B_TREE; i++) {
    if (fread(&page->childPointer[i], sizeof(int), 1, f_arvore_B) != 1)
      return false;
  }

  return true;
}

bool read_B_tree_header_from_bin(FILE *f_arvore_B, HEADER_BT *header) {
  if (fseek(f_arvore_B, 0, SEEK_SET) != 0)
    return false;

  if (fread(&header->status, sizeof(char), 1, f_arvore_B) != 1)
    return false;

  if (fread(&header->rootPage, sizeof(int), 1, f_arvore_B) != 1)
    return false;

  if (fread(&header->topOfStack, sizeof(int), 1, f_arvore_B) != 1)
    return false;

  if (fread(&header->nextRRN, sizeof(int), 1, f_arvore_B) != 1)
    return false;

  if (fread(&header->numOfPages, sizeof(int), 1, f_arvore_B) != 1)
    return false;

  return true;
}

bool write_B_tree_page_in_bin(FILE *f_arvore_B, PAGE *page, int RRN) {
  // Pula para a pagina(no) do RRN solicitado
  if (fseek(f_arvore_B, PAGE_OFFSET_B_TREE(RRN), SEEK_SET) != 0)
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

    int key = (i < page->numOfKeys) ? page->keys[i].value : -1;

    int byteOffset = (i < page->numOfKeys) ? page->keys[i].byteOffset : -1;

    if (fwrite(&key, sizeof(int), 1, f_arvore_B) != 1)
      return false;

    if (fwrite(&byteOffset, sizeof(int), 1, f_arvore_B) != 1)
      return false;
  }

  for (int i = 0; i < MAX_CHILDREN_B_TREE; i++) {

    int child = (i <= page->numOfKeys) ? page->childPointer[i] : -1;

    if (fwrite(&child, sizeof(int), 1, f_arvore_B) != 1)
      return false;
  }

  return true;
}

bool write_B_tree_header_in_bin(FILE *f_arvore_B, HEADER_BT *header) {
  if (fseek(f_arvore_B, 0, SEEK_SET) != 0)
    return false;

  if (fwrite(&header->status, sizeof(char), 1, f_arvore_B) != 1)
    return false;

  if (fwrite(&header->rootPage, sizeof(int), 1, f_arvore_B) != 1)
    return false;

  if (fwrite(&header->topOfStack, sizeof(int), 1, f_arvore_B) != 1)
    return false;

  if (fwrite(&header->nextRRN, sizeof(int), 1, f_arvore_B) != 1)
    return false;

  if (fwrite(&header->numOfPages, sizeof(int), 1, f_arvore_B) != 1)
    return false;

  return true;
}



void builder_header_B_tree(HEADER_BT *header, char status, int rootPage,
                           int topOfStack, int nextRRN, int numOfPages) {
  header->status = status;
  header->rootPage = rootPage;
  header->topOfStack = topOfStack;
  header->nextRRN = nextRRN;
  header->numOfPages = numOfPages;
}



int get_next_available_RRN_in_B_tree(FILE *f_arvore_B, HEADER_BT *header) {

  int rrn_disponivel;

  // Verifica se existe alguma página logicamente removida na pilha
  if (header->topOfStack != -1) {

    // O RRN disponível será o que estava no topo da pilha
    rrn_disponivel = header->topOfStack;

    // Precisamos ler essa página removida para descobrir quem é o próximo da
    // pilha
    PAGE page;

    if (!read_B_tree_page_from_bin(f_arvore_B, &page, rrn_disponivel)) {
      return -1;
    }

    // Atualiza o topo da pilha no cabeçalho com o próximo RRN da lista
    // encadeada
    header->topOfStack = page.nextInStack;

  } else {

    // Se não houver páginas removidas, pega o próximo RRN livre do fim do
    // arquivo
    rrn_disponivel = header->nextRRN;

    // Incrementa o próximo RRN livre
    header->nextRRN++;
  }

  return rrn_disponivel;
}

int get_filepointer_value_from_key(FILE *f_arvore_B, int key, int RRN,
                                   int index) {

  // Verifica se o index e maior que o limite de chaves
  if (index >= MAX_KEYS_PER_PAGE_B_TREE)
    return -1;

  PAGE page;

  if (!read_B_tree_page_from_bin(f_arvore_B, &page, RRN))
    return -1;

  if (page.removed == '1') {
    printf("erro ao tentar pegar chave em pagina removida");
    return -1;
  }

  if (page.keys[index].value != key)
    return -1;

  return page.keys[index].byteOffset;
}
