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
  char status; // 0 = inconsistente
  int rootPage;
  int topOfStack;
  int nextRRN;
  int numOfPages;
} HEADER_BT;

typedef struct key_bt {
  int value;
  int byteOffset;
} KEY;

#define PAGE_SIZE_B_TREE 53

#define PAGE_OFFSET_B_TREE(rrn)                                                \
  (HEADER_SIZE_B_TREE + ((rrn) * PAGE_SIZE_B_TREE))

#define PAGE_REMOVED_POSITION_B_TREE 0
#define PAGE_NEXT_IN_STACK_POSITION_B_TREE 1
#define PAGE_PAGE_TYPE_POSITION_B_TREE 5
#define PAGE_NUM_OF_KEYS_POSITION_B_TREE 9
#define PAGE_KEYS_POSITION_B_TREE 13
#define PAGE_CHILD_POINTER_POSITION_B_TREE 37

typedef struct page {
  char removed; // 1 = removed
  int nextInStack;
  int pageType; // -1=folha , 0=raiz , 1=intermediario
  int numOfKeys;

  KEY keys[MAX_KEYS_PER_PAGE_B_TREE];

  int childPointer[MAX_CHILDREN_B_TREE];

} PAGE;

// Funcoes Auxiliares
/* leitura de página */

/* busca */

#define ERROR -1

#define NOT_IN_PAGE 0
#define IN_PAGE 1
// int find_key(FILE *f_arvore_B, PAGE *page, int RRN, int key, int *key_INDEX,
//              int *page_RRN);

int find_key_in_page(PAGE *page, int key, int *supost_position);

/* acesso direto */

bool read_B_tree_page_from_bin(FILE *f_arvore_B, PAGE *page, int RRN);

bool read_B_tree_header_from_bin(FILE *f_arvore_B, HEADER_BT *header);

bool write_B_tree_page_in_bin(FILE *f_arvore_B, PAGE *page, int RRN);

bool write_B_tree_header_in_bin(FILE *f_arvore_B, HEADER_BT *header);

int get_next_available_RRN_in_B_tree(FILE *f_arvore_B, HEADER_BT *header);

int get_filepointer_value_from_key(FILE *f_arvore_B, int key, int rrn,
                                   int index);

/* Inserir */

#define PROMOTION 1
#define NO_PROMOTION 0

bool insert_key(FILE *f_arvore_B, HEADER_BT *header, KEY key);

#endif
