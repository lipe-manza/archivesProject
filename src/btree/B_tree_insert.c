#include <stdbool.h>

#include "../../headers/B_tree.h"

#define MAX_KEYS_SPLIT_PAGE (MAX_KEYS_PER_PAGE_B_TREE + 1)
#define MAX_CHILDREN_SPLIT_PAGE (MAX_CHILDREN_B_TREE + 1)

void insert_bt(FILE *f_bt, HEADER_BT *hdr_bt, KEY *key) {
  if (f_bt == NULL || hdr_bt == NULL || key == NULL)
    return;

  int RRN_ant = -1;
  int RRN = hdr_bt->rootPage;

  // Inserção da primeira chave
  if (hdr_bt->rootPage == -1) {
    PAGE page;
    pag
  }

  int pos_p = 0;
  PAGE page;

  while (RRN != 0) {
    if (!read_B_tree_page_from_bin(f_bt, &page, hdr_bt->rootPage))
      return; // ERRO NA LEITURA DO ARQUIVO

    for (int i = 0; i < MAX_KEYS_PER_PAGE_B_TREE; i++) {
      pos_p = 0;

      // Está em um nó folha e há espaço para uma chave
      if (page.pageType == PAGE_TYPE_LEAF &&
          page.numOfKeys < MAX_KEYS_PER_PAGE_B_TREE) {
        // Func aux
        return;
      }
      if (page.keys[i].value == key->value)
        return; // TENTANDO INSERIR CHAVE QUE JÁ ESTÁ NA BT
      if (page.keys[i].value < key->value)
        break;
      pos_p++;
      RRN_ant = RRN;
    }
    RRN = page.childPointer[pos_p];
  }

  // Agora reordena
}

typedef struct splitPage {
  int numOfKeys;

  KEY keys[MAX_KEYS_SPLIT_PAGE];

  int childPointer[MAX_CHILDREN_SPLIT_PAGE];
} SPLITPAGE;

static int determine_page_type(PAGE *page) {
  for (int i = 0; i <= page->numOfKeys; i++) {
    if (page->childPointer[i] != -1)
      return 1; // Intermediario
  }

  return -1; // Folha
}

static int insert_ordened_into_splitPage(SPLITPAGE *page, KEY insertKey,
                                         int insertChildPointer) {
  int i = 0;

  while (i < page->numOfKeys && insertKey.value > page->keys[i].value)
    i++;

  for (int j = page->numOfKeys; j > i; j--) {
    page->keys[j] = page->keys[j - 1];
    page->childPointer[j + 1] = page->childPointer[j];
  }

  page->keys[i] = insertKey;
  page->childPointer[i + 1] = insertChildPointer;

  page->numOfKeys++;

  return i;
}

int insert_ordened_in_page(PAGE *page, KEY insertKey, int insertChildPointer) {
  int i = 0;

  while (i < page->numOfKeys && insertKey.value > page->keys[i].value)
    i++;

  for (int j = page->numOfKeys; j > i; j--) {
    page->keys[j] = page->keys[j - 1];
    page->childPointer[j + 1] = page->childPointer[j];
  }

  page->keys[i] = insertKey;
  page->childPointer[i + 1] = insertChildPointer;

  page->numOfKeys++;

  return i;
}

bool split(PAGE *page, PAGE *newPage, KEY insertKey, int insertchildpointer,
           KEY *promotionKey) {

  SPLITPAGE sp;
  int i;

  // Inicializa as structs e os vetores das structs

  /* SPLITPAGE*/
  sp.numOfKeys = 0;
  for (int i = 0; i < MAX_CHILDREN_SPLIT_PAGE; i++) {
    sp.childPointer[i] = -1;
    if (i < MAX_KEYS_SPLIT_PAGE) {
      sp.keys[i].value = -1;
      sp.keys[i].byteOffset = -1;
    }
  }
  /* newPage */

  for (int i = 0; i < MAX_CHILDREN_B_TREE; i++) {
    newPage->childPointer[i] = -1;
    if (i < MAX_KEYS_PER_PAGE_B_TREE) {
      newPage->keys[i].value = -1;
      newPage->keys[i].byteOffset = -1;
    }
  }

  // Preenche o splitPage com os valores da pagina da esquerda
  sp.numOfKeys = page->numOfKeys;

  for (i = 0; i < page->numOfKeys; i++) {
    sp.keys[i] = page->keys[i];
  }

  for (i = 0; i <= page->numOfKeys; i++) {
    sp.childPointer[i] = page->childPointer[i];
  }

  // Insere ordenadamente na splitPage
  insert_ordened_into_splitPage(&sp, insertKey, insertchildpointer);

  // Calcula a separacao da sp e seta o promotionKey como a menor da direita
  int total = sp.numOfKeys;
  int mid = total / 2;

  *promotionKey = sp.keys[mid];

  /* pagina da esquerda*/
  page->numOfKeys = mid;

  for (i = 0; i < mid; i++) {
    page->keys[i] = sp.keys[i];
  }

  for (i = mid; i < MAX_KEYS_PER_PAGE_B_TREE; i++) {
    page->keys[i].value = -1;
    page->keys[i].byteOffset = -1;
  }

  for (i = 0; i <= mid; i++) {
    page->childPointer[i] = sp.childPointer[i];
  }

  for (i = mid + 1; i < MAX_CHILDREN_B_TREE; i++) {
    page->childPointer[i] = -1;
  }

  /* pagina da direita*/
  newPage->removed = '0';
  newPage->nextInStack = -1;
  newPage->numOfKeys = total - mid - 1;

  // O leftChildPointer da primeira Key na pagina da direita
  // vai ser o rightChildPointer da promotionKey de index[mid]
  newPage->childPointer[0] = sp.childPointer[mid + 1];

  int j = 0;

  for (i = mid + 1; i < total; i++) {
    newPage->keys[j] = sp.keys[i];
    newPage->childPointer[j + 1] = sp.childPointer[i + 1];
    j++;
  }

  for (; j < MAX_KEYS_PER_PAGE_B_TREE; j++) {
    newPage->keys[j].value = -1;
    newPage->keys[j].byteOffset = -1;
  }

  for (i = newPage->numOfKeys + 1; i < MAX_CHILDREN_B_TREE; i++) {
    newPage->childPointer[i] = -1;
  }

  page->pageType = determine_page_type(page);
  newPage->pageType = determine_page_type(newPage);

  return true;
}

int insert_key_aux(FILE *f_arvore_B, HEADER_BT *header, int currentRRN, KEY key,
                   KEY *promotionKey, int *promotionRightChild) {

  if (currentRRN == -1) {
    *promotionKey = key;
    *promotionRightChild = -1;

    return PROMOTION;
  }

  PAGE currentPage;

  if (!read_B_tree_page_from_bin(f_arvore_B, &currentPage, currentRRN))
    return ERROR;

  int pos;

  int found = find_key_in_page(&currentPage, key.value, &pos);

  if (found == IN_PAGE)
    return ERROR;

  KEY promotedKey;
  int promotedRightRRN;

  int status = insert_key_aux(f_arvore_B, header, currentPage.childPointer[pos],
                              key, &promotedKey, &promotedRightRRN);

  if (status == ERROR || status == NO_PROMOTION)
    return status;

  if (currentPage.numOfKeys < MAX_KEYS_PER_PAGE_B_TREE) {

    insert_ordened_in_page(&currentPage, promotedKey, promotedRightRRN);

    if (!write_B_tree_page_in_bin(f_arvore_B, &currentPage, currentRRN))
      return ERROR;

    return NO_PROMOTION;
  }

  PAGE newPage;

  int newRRN = get_next_available_RRN_in_B_tree(f_arvore_B, header);

  if (newRRN == -1)
    return ERROR;

  split(&currentPage, &newPage, promotedKey, promotedRightRRN, promotionKey);

  *promotionRightChild = newRRN;

  if (!write_B_tree_page_in_bin(f_arvore_B, &currentPage, currentRRN))
    return ERROR;

  if (!write_B_tree_page_in_bin(f_arvore_B, &newPage, newRRN))
    return ERROR;

  header->numOfPages++;

  return PROMOTION;
}

bool create_new_root(FILE *f_arvore_B, HEADER_BT *header, KEY key,
                     int promotedRightRRN) {
  PAGE newRoot;

  newRoot.removed = '0';
  newRoot.nextInStack = -1;
  newRoot.pageType = 0;
  newRoot.numOfKeys = 1;

  int newRootRRN = get_next_available_RRN_in_B_tree(f_arvore_B, header);

  newRoot.keys[0] = key;

  for (int i = 1; i < MAX_KEYS_PER_PAGE_B_TREE; i++) {
    newRoot.keys[i].value = -1;
    newRoot.keys[i].byteOffset = -1;
  }

  newRoot.childPointer[0] = header->rootPage;
  newRoot.childPointer[1] = promotedRightRRN;

  for (int i = 2; i < MAX_CHILDREN_B_TREE; i++) {
    newRoot.childPointer[i] = -1;
  }

  if (!write_B_tree_page_in_bin(f_arvore_B, &newRoot, newRootRRN))
    return false;

  header->numOfPages++;
  header->rootPage = newRootRRN;

  if (!write_B_tree_header_in_bin(f_arvore_B, header))
    return false;

  return true;
}

bool insert_key(FILE *f_arvore_B, HEADER_BT *header, KEY key) {

  KEY promotedKey;
  int promotedRightRRN;

  int status = insert_key_aux(f_arvore_B, header, header->rootPage, key,
                              &promotedKey, &promotedRightRRN);

  if (status == ERROR)
    return false;

  if (status == NO_PROMOTION)
    return true;

  if (!create_new_root(f_arvore_B, header, promotedKey, promotedRightRRN))
    return false;

  return true;
}
