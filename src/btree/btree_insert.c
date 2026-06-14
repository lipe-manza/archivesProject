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
  int top_stack = btree_header_get_top_of_stack(header);
  int available_rrn;

  // Se o topo for diferente de -1 então usa a lógica da pilha de remoções
  if (top_stack != -1) {
    available_rrn = top_stack;

    // Cria uma página auxiliar para pegar o proximo da pilha e atualizar o
    // header
    BTreePage *removed_page = btree_page_create();
    if (!btree_page_read(bin_file, removed_page, available_rrn)) {
      btree_page_destroy(&removed_page);
      return BTREE_ERROR;
    }

    // Atualiza o topo da pilha para o próximo da lista encadeada
    btree_header_set_top_of_stack(header,
                                  btree_page_get_next_in_stack(removed_page));
    btree_page_destroy(&removed_page);
  } else { // Caso não existam páginas logicamente removidas pega o próximo rrn
           // disponível
    available_rrn = btree_header_get_next_rrn(header);
    btree_header_set_next_rrn(header, available_rrn + 1);
  }

  return available_rrn;
}

// Busca a posição em que uma chave deveria estar/inserida dentro de uma
// página. Retorna true se a chave já existe
static bool search_position_in_page(BTreePage *page, int search_key, int *pos) {
  int num_keys = btree_page_get_num_of_keys(page);

  for (int i = 0; i < num_keys; i++) {
    BTreeKey current = btree_page_get_key(page, i);
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
  int num_keys = btree_page_get_num_of_keys(page);
  int pos = 0;

  // Acha posição
  while (pos < num_keys && insert_key.C > btree_page_get_key(page, pos).C) {
    pos++;
  }

  // Shift para a direita usando os setters/getters
  for (int i = num_keys; i > pos; i--) {
    btree_page_set_key(page, i, btree_page_get_key(page, i - 1));
    btree_page_set_child_pointer(page, i + 1,
                                 btree_page_get_child_pointer(page, i));
  }

  btree_page_set_key(page, pos, insert_key);
  btree_page_set_child_pointer(page, pos + 1, right_child_rrn);
  btree_page_set_num_of_keys(page, num_keys + 1);
}

// Faz o split na página quando não há espaço disponível e teve promoção da key
static void perform_split(BTreePage *left_page, BTreePage *right_page,
                          BTreeKey new_key, int new_right_child,
                          BTreeKey *promoted_key) {
  // página auxiliar
  SplitPage sp;
  sp.num_keys = btree_page_get_num_of_keys(left_page);

  // Copia dados da página cheia(da esquerda) para a SplitPage
  for (int i = 0; i < sp.num_keys; i++) {
    sp.keys[i] = btree_page_get_key(left_page, i);
    sp.children[i] = btree_page_get_child_pointer(left_page, i);
  }
  // Termina de passar os childPointers
  sp.children[sp.num_keys] =
      btree_page_get_child_pointer(left_page, sp.num_keys);

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
  btree_page_set_num_of_keys(left_page, mid);
  for (int i = 0; i < BTREE_MAX_KEYS; i++) {
    if (i < mid) {
      btree_page_set_key(left_page, i, sp.keys[i]);
      btree_page_set_child_pointer(left_page, i, sp.children[i]);
    } else {
      btree_page_set_key(left_page, i, (BTreeKey){-1, -1});
      btree_page_set_child_pointer(left_page, i, -1);
    }
  }
  btree_page_set_child_pointer(left_page, mid,
                               sp.children[mid]); // Último filho da esquerda
  btree_page_set_child_pointer(left_page, mid + 1,
                               -1); // Termina de setar o último child_pointer

  // Constrói a Right Page (mid + 1 até o fim)
  btree_page_set_removed(right_page, '0');
  btree_page_set_next_in_stack(right_page, -1);
  btree_page_set_num_of_keys(right_page, sp.num_keys - mid - 1);

  if (btree_page_get_page_type(left_page) == PAGE_TYPE_ROOT) {
    btree_page_set_page_type(left_page, PAGE_TYPE_MID);
  }

  // Se a esquerda era folha, a direita também será. Se era intermediário, a
  // direita também será.
  btree_page_set_page_type(right_page, btree_page_get_page_type(left_page));

  int j = 0;
  // Seta o child_pointer(filho da esquerda) da página da direita como o
  // childPointer da promoted_key
  btree_page_set_child_pointer(right_page, 0, sp.children[mid + 1]);

  for (int i = mid + 1; i < sp.num_keys; i++) {
    btree_page_set_key(right_page, j, sp.keys[i]);
    btree_page_set_child_pointer(right_page, j + 1, sp.children[i + 1]);
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
  BTreePage *page = btree_page_create();
  if (!btree_page_read(bin_file, page, current_rrn)) {
    btree_page_destroy(&page);
    return BTREE_ERROR;
  }

  int pos;
  if (search_position_in_page(page, key.C, &pos)) {
    btree_page_destroy(&page);
    return BTREE_ERROR; // Chave já existe
  }

  // Variáveis auxiliares do retorno da recursão
  BTreeKey returned_key;
  int returned_right_rrn;

  // Desce recursivamente
  int status = insert_recursive(bin_file, header,
                                btree_page_get_child_pointer(page, pos), key,
                                &returned_key, &returned_right_rrn);

  if (status == BTREE_NO_PROMOTION || status == BTREE_ERROR) {
    btree_page_destroy(&page);
    return status;
  }

  // Se houve promoção do nível inferior, tenta inserir na página atual se ela
  // tiver espaço
  if (btree_page_get_num_of_keys(page) < BTREE_MAX_KEYS) {
    insert_into_page_with_space(page, returned_key, returned_right_rrn);
    bool write_ok = btree_page_write(bin_file, page, current_rrn);
    btree_page_destroy(&page);
    return write_ok ? BTREE_NO_PROMOTION : BTREE_ERROR;
  }

  // Se chegou aqui, significa que a página atual está cheia e precisa fazer
  // split
  BTreePage *new_right_page = btree_page_create();
  int new_rrn = get_next_available_rrn(bin_file, header);

  perform_split(page, new_right_page, returned_key, returned_right_rrn,
                promoted_key);
  *promoted_right_rrn = new_rrn;

  // Atualiza disco
  btree_page_write(bin_file, page, current_rrn);
  btree_page_write(bin_file, new_right_page, new_rrn);
  // Atualiza a contagem de nós
  btree_header_set_node_count(header, btree_header_get_node_count(header) + 1);

  btree_page_destroy(&page);
  btree_page_destroy(&new_right_page);

  return BTREE_PROMOTION;
}

// ==================== Função Pública ====================

bool btree_insert_key(FILE *bin_file, BTreeHeader *header, BTreeKey key) {
  if (bin_file == NULL || header == NULL)
    return false;
  // Variávies auxiliares
  BTreeKey promoted_key;
  int promoted_right_rrn;
  int root_rrn = btree_header_get_root_node(header);

  int status = insert_recursive(bin_file, header, root_rrn, key, &promoted_key,
                                &promoted_right_rrn);

  if (status == BTREE_ERROR)
    return false;

  // Caso haja promoção na raiz ou árvore vazia
  // Cria uma nova página para ser a raíz
  if (status == BTREE_PROMOTION) {
    // Página da nova raiz
    BTreePage *new_root = btree_page_create();
    int new_root_rrn = get_next_available_rrn(bin_file, header);

    // Quando a árvore está vazia
    if (promoted_right_rrn == -1) {
      btree_page_set_page_type(new_root,
                               PAGE_TYPE_LEAF); // Quando nó-folha = nó-raiz
    } else {
      btree_page_set_page_type(new_root, PAGE_TYPE_ROOT); // Raiz normal
    }

    btree_page_set_num_of_keys(new_root, 1);
    btree_page_set_key(new_root, 0, promoted_key);
    btree_page_set_child_pointer(new_root, 0, root_rrn);
    btree_page_set_child_pointer(new_root, 1, promoted_right_rrn);

    btree_page_write(bin_file, new_root, new_root_rrn);

    btree_header_set_root_node(header, new_root_rrn);
    btree_header_set_node_count(header,
                                btree_header_get_node_count(header) + 1);
    btree_header_write(bin_file, header);

    btree_page_destroy(&new_root);
  }

  return true;
}
