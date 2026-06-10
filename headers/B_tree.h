#ifndef PAGE_H
#define PAGE_H

#include <stdbool.h>
#include <stdio.h>

#define B_TREE_ORDER 4
#define MAX_KEYS_PER_PAGE_B_TREE 3
#define MIN_KEYS_PER_PAGE_B_TREE 1
#define MAX_CHILDREN_B_TREE 4
#define MIN_CHILDREN_B_TREE 2

#define HEADER_SIZE_B_TREE 17

#define HEADER_STATUS_POSITION_B_TREE 0
#define HEADER_ROOTPAGE_POSITION_B_TREE 1
#define HEADER_TOP_OF_STACK_POSITION_B_TREE 5
#define HEADER_NEXT_RRN_POSITION_B_TREE 9
#define HEADER_NUM_OF_PAGES_POSITION_B_TREE 13

typedef struct header_B_tree {
  char status;
  int rootPage;
  int topOfStack;
  int nextRRN;
  int numOfPages;
} HEADER_B_TREE;

#define PAGE_SIZE_B_TREE 53

#define PAGE_REMOVED_POSITION_B_TREE 0
#define PAGE_NEXT_IN_STACK_POSITION_B_TREE 1
#define PAGE_PAGE_TYPE_POSITION_B_TREE 5
#define PAGE_NUM_OF_KEYS_POSITION_B_TREE 9
#define PAGE_KEYS_POSITION_B_TREE 13
#define PAGE_ARCHIVE_POINTER_POSITION_B_TREE 17
#define PAGE_CHILD_POINTER_POSITION_B_TREE 37

typedef struct page {
  char removed; // 0 = inconsistente
  int nextInStack;
  int pageType;
  int numOfKeys;
  int keys[MAX_KEYS_PER_PAGE_B_TREE];
  int filePointer[MAX_KEYS_PER_PAGE_B_TREE];
  int childPointer[MAX_CHILDREN_B_TREE];

} PAGE;
// Funções principais
bool find_key(FILE *f_arvore_B, PAGE *page, int RRN, int key, int *key_INDEX,
              int *page_RRN);
// Funcoes Auxiliares
/* leitura de página */
bool get_B_tree_page(FILE *f_arvore_B, PAGE *page, int RRN);

/* busca */
bool find_key_in_page(FILE *f_arvore_B, int key, int RRN, int *supost_position);

/* acesso direto */
int get_filePointer_value_from_key(FILE *f_arvore_B, int key, int RRN,
                                   int index);

#endif
