#include "../../include/btree.h"

int btree_search_key(FILE *bin_file, BTreeHeader *header, int search_key) {
  if (bin_file == NULL || header == NULL) {
    return BTREE_NOT_FOUND;
  }

  int current_rrn = header->noRaiz;

  // Se a raiz é -1, a árvore está vazia
  if (current_rrn == -1) {
    return BTREE_NOT_FOUND;
  }

  // Inicializa a página
  BTreePage page;

  int found_offset = BTREE_NOT_FOUND;

  // Busca iterativa: desce na árvore até achar a chave ou bater num filho nulo
  while (current_rrn != -1) {
    // Lê a página atual do disco
    if (!btree_page_read(bin_file, &page, current_rrn)) {
      break; // Erro de leitura, aborta a busca
    }

    // Proteção contra corrupção lógica: não deveríamos visitar nós removidos
    if (page.removido == '1') {
      break;
    }

    int num_keys = page.nroChaves;
    int i = 0;

    // Varre as chaves da página atual para encontrar o caminho ou a própria
    // chave
    while (i < num_keys) {
      BTreeKey current = page.chaves[i];

      if (current.C == search_key) {
        // Achou a chave! Guarda o offset e interrompe o laço interno
        found_offset = current.Pr;
        break;
      } else if (current.C > search_key) {
        // A chave buscada é menor, então deve estar no filho à esquerda desta
        // chave
        break;
      }
      // Se for maior, continua testando as próximas chaves da página
      i++;
    }

    // Se achou, interrompe o laço externo (while) de descida na árvore
    if (found_offset != BTREE_NOT_FOUND) {
      break;
    }

    // Atualiza o RRN para descer para a página filha correspondente
    current_rrn = page.P[i];
  }

  return found_offset;
}
