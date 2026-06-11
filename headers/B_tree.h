#ifndef PAGE_H
#define PAGE_H

#include <stdbool.h>
#include <stdio.h>

#define ERROR -1

#define NOT_IN_PAGE 0
#define IN_PAGE 1

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
#define PAGE_FILE_POINTER_POSITION_B_TREE 17
#define PAGE_CHILD_POINTER_POSITION_B_TREE 37

typedef struct page {
  char removed; // 1 = removed
  int nextInStack;
  int pageType;
  int numOfKeys;
  int keys[MAX_KEYS_PER_PAGE_B_TREE];
  int filePointer[MAX_KEYS_PER_PAGE_B_TREE];
  int childPointer[MAX_CHILDREN_B_TREE];

} PAGE;

// Funcoes Auxiliares
/* leitura de página */
bool get_B_tree_page(FILE *f_arvore_B, PAGE *page, int RRN);

/* busca */

int find_key(FILE *f_arvore_B, PAGE *page, int RRN, int key, int *key_INDEX,
             int *page_RRN);

int find_key_in_page(FILE *f_arvore_B, PAGE *page, int key,
                     int *supost_position);

/* acesso direto */

int get_filePointer_value_from_key(FILE *f_arvore_B, int key, int RRN,
                                   int index);
bool read_B_tree_page_from_bin(FILE *f_arvore_B, PAGE *page, int RRN);

bool write_B_tree_page_from_bin(FILE *f_arvore_B, PAGE *page, int RRN);

/* Inserir */
#define PROMOTION 1
#define NO_PROMOTION 0

int insert();
#endif
