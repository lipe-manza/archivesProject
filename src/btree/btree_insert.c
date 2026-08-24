#include "../../include/btree.h"
#include <stdlib.h>

// ==================== Estruturas Auxiliares Privadas ====================

// Página split(auxiliar) usada na Ram durante o split
typedef struct {
  int num_keys;
  BTreeKey keys[BTREE_MAX_KEYS + 1];
  int children[BTREE_MAX_CHILDREN + 1];
} SplitPage;

// ==================== Funções Auxiliares (Static) ====================

// Pega o próximo RRN disponível.
static int get_next_available_rrn(FILE *bin_file, BTreeHeader *header) {
  // Pega o topo da pilha no cabeçalho
  int top_stack = header->topo;
  int available_rrn;

  // Se o topo for diferente de -1 então usa a lógica da pilha de remoções
  if (top_stack != -1) {
    available_rrn = top_stack;

    // Cria uma página auxiliar para pegar o proximo da pilha e atualizar o
    // header
    BTreePage removed_page;
    if (!btree_page_read(bin_file, &removed_page, available_rrn)) {
      return BTREE_ERROR;
    }

    // Atualiza o topo da pilha para o próximo da lista encadeada
    header->topo = removed_page.proximo;
  } else { // Caso não existam páginas logicamente removidas pega o próximo rrn
           // disponível
    available_rrn = header->proxRRN;
    header->proxRRN = available_rrn + 1;
  }

  return available_rrn;
}

// Busca a posição em que uma chave deveria estar/inserida dentro de uma
// página. Retorna true se a chave já existe
static bool search_position_in_page(BTreePage *page, int search_key, int *pos) {
  int num_keys = page->nroChaves;

  for (int i = 0; i < num_keys; i++) {
    BTreeKey current = page->chaves[i];
    if (current.C == search_key) {
      *pos = i;
      return true; // Chave já existe
    }
    if (current.C > search_key) {
      *pos = i;
      return false; // Achou a posição de descida/inserção
    }
  }

  *pos = num_keys; // Maior que todas, vai no último ponteiro
  return false;
}

// Insere ordenadamente em uma página que tem espaço
static void insert_into_page_with_space(BTreePage *page, BTreeKey insert_key,
                                        int right_child_rrn) {
  int num_keys = page->nroChaves;
  int pos = 0;

  // Acha posição
  while (pos < num_keys && insert_key.C > page->chaves[pos].C) {
    pos++;
  }

  // Shift para a direita
  for (int i = num_keys; i > pos; i--) {
    page->chaves[i] = page->chaves[i - 1];
    page->P[i + 1] = page->P[i];
  }

  page->chaves[pos] = insert_key;
  page->P[pos + 1] = right_child_rrn;
  page->nroChaves = num_keys + 1;
}

// Faz o split na página quando não há espaço disponível e teve promoção da key
static void perform_split(BTreePage *left_page, BTreePage *right_page,
                          BTreeKey new_key, int new_right_child,
                          BTreeKey *promoted_key) {
  // página auxiliar
  SplitPage sp;
  sp.num_keys = left_page->nroChaves;

  // Copia dados da página cheia(da esquerda) para a SplitPage
  for (int i = 0; i < sp.num_keys; i++) {
    sp.keys[i] = left_page->chaves[i];
    sp.children[i] = left_page->P[i];
  }
  // Termina de passar os childPointers
  sp.children[sp.num_keys] = left_page->P[sp.num_keys];

  // Insere a nova chave ordenadamente na SplitPage
  int pos = 0;
  while (pos < sp.num_keys && new_key.C > sp.keys[pos].C)
    pos++;
  // Caso a posição da key não seja a ultima desloca para conseguir espaço
  for (int i = sp.num_keys; i > pos; i--) {
    sp.keys[i] = sp.keys[i - 1];
    sp.children[i + 1] = sp.children[i];
  }
  sp.keys[pos] = new_key;
  sp.children[pos + 1] = new_right_child;
  sp.num_keys++;

  // Calcula a promoção (mid = 2 no caso de m=4)
  int mid = sp.num_keys / 2;
  *promoted_key = sp.keys[mid];

  // Limpa e reconstrói a Left Page (0 até mid - 1)
  left_page->nroChaves = mid;
  for (int i = 0; i < BTREE_MAX_KEYS; i++) {
    if (i < mid) {
      left_page->chaves[i] = sp.keys[i];
      left_page->P[i] = sp.children[i];
    } else {
      left_page->chaves[i] = (BTreeKey){-1, -1};
      left_page->P[i] = -1;
    }
  }
  left_page->P[mid] = sp.children[mid]; // Último filho da esquerda
  left_page->P[mid + 1] = -1; // Termina de setar o último child_pointer

  // Constrói a Right Page (mid + 1 até o fim)
  right_page->removido = '0';
  right_page->proximo = -1;
  right_page->nroChaves = sp.num_keys - mid - 1;

  if (left_page->tipoNo == PAGE_TYPE_ROOT) {
    left_page->tipoNo = PAGE_TYPE_MID;
  }

  // Se a esquerda era folha, a direita também será. Se era intermediário, a
  // direita também será.
  right_page->tipoNo = left_page->tipoNo;

  int j = 0;
  // Seta o child_pointer(filho da esquerda) da página da direita como o
  // childPointer da promoted_key
  right_page->P[0] = sp.children[mid + 1];

  for (int i = mid + 1; i < sp.num_keys; i++) {
    right_page->chaves[j] = sp.keys[i];
    right_page->P[j + 1] = sp.children[i + 1];
    j++;
  }
}

// Função recursiva de descida e inserção.
static int insert_recursive(FILE *bin_file, BTreeHeader *header,
                            int current_rrn, BTreeKey key,
                            BTreeKey *promoted_key, int *promoted_right_rrn) {
  // Chegou no fundo (folha virtual), propaga a promoção da chave original
  if (current_rrn == -1) {
    *promoted_key = key;
    *promoted_right_rrn = -1;
    return BTREE_PROMOTION;
  }

  // lê a página atual
  BTreePage page;
  if (!btree_page_read(bin_file, &page, current_rrn)) {
    return BTREE_ERROR;
  }

  int pos;
  if (search_position_in_page(&page, key.C, &pos)) {
    return BTREE_ERROR; // Chave já existe
  }

  // Variáveis auxiliares do retorno da recursão
  BTreeKey returned_key;
  int returned_right_rrn;

  // Desce recursivamente
  int status = insert_recursive(bin_file, header,
                                page.P[pos], key,
                                &returned_key, &returned_right_rrn);

  if (status == BTREE_NO_PROMOTION || status == BTREE_ERROR) {
    return status;
  }

  // Se houve promoção do nível inferior, tenta inserir na página atual se ela
  // tiver espaço
  if (page.nroChaves < BTREE_MAX_KEYS) {
    insert_into_page_with_space(&page, returned_key, returned_right_rrn);
    bool write_ok = btree_page_write(bin_file, &page, current_rrn);
    return write_ok ? BTREE_NO_PROMOTION : BTREE_ERROR;
  }

  // Se chegou aqui, significa que a página atual está cheia e precisa fazer
  // split
  BTreePage new_right_page;
  int new_rrn = get_next_available_rrn(bin_file, header);

  perform_split(&page, &new_right_page, returned_key, returned_right_rrn,
                promoted_key);
  *promoted_right_rrn = new_rrn;

  // Atualiza disco
  btree_page_write(bin_file, &page, current_rrn);
  btree_page_write(bin_file, &new_right_page, new_rrn);
  // Atualiza a contagem de nós
  header->nroNos = header->nroNos + 1;

  return BTREE_PROMOTION;
}

// ==================== Função Pública ====================

bool btree_insert_key(FILE *bin_file, BTreeHeader *header, BTreeKey key) {
  if (bin_file == NULL || header == NULL)
    return false;
  // Variávies auxiliares
  BTreeKey promoted_key;
  int promoted_right_rrn;
  int root_rrn = header->noRaiz;

  int status = insert_recursive(bin_file, header, root_rrn, key, &promoted_key,
                                &promoted_right_rrn);

  if (status == BTREE_ERROR)
    return false;

  // Caso haja promoção na raiz ou árvore vazia
  // Cria uma nova página para ser a raíz
  if (status == BTREE_PROMOTION) {
    // Página da nova raiz
    BTreePage new_root;
    int new_root_rrn = get_next_available_rrn(bin_file, header);

    // Quando a árvore está vazia
    if (promoted_right_rrn == -1) {
      new_root.tipoNo = PAGE_TYPE_LEAF; // Quando nó-folha = nó-raiz
    } else {
      new_root.tipoNo = PAGE_TYPE_ROOT; // Raiz normal
    }

    new_root.nroChaves = 1;
    new_root.chaves[0] = promoted_key;
    new_root.P[0] = root_rrn;
    new_root.P[1] = promoted_right_rrn;

    // Inicializa o resto com -1
    for (int i = 1; i < BTREE_MAX_KEYS; i++) {
        new_root.chaves[i] = (BTreeKey){-1, -1};
    }
    for (int i = 2; i < BTREE_MAX_CHILDREN; i++) {
        new_root.P[i] = -1;
    }
    new_root.removido = '0';
    new_root.proximo = -1;

    btree_page_write(bin_file, &new_root, new_root_rrn);

    header->noRaiz = new_root_rrn;
    header->nroNos = header->nroNos + 1;
    btree_header_write(bin_file, header);
  }

  return true;
}
