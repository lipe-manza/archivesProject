// Luiz Felipe Manzoli Franceschini - 16913300
// Enzo Trulenque Evangelista - 15819219

#include <stdio.h>

#include "../include/sql_functions.h"

int main() {
  int n = 0;

  // Lê o número da operação
  if (scanf("%d", &n) != 1)
    return 0;

  switch (n) {
  case 1: // CREATE TABLE
    create_table();
    break;
  case 2: // SELECT FROM
    select_from();
    break;
  case 3: // SELECT FROM WHERE
    select_from_where();
    break;
  case 4: // DELETE FROM WHERE
    delete_from_where();
    break;
  case 5: // INSERT INTO
    insert_into();
    break;
  case 6: // UPDATE SET WHERE
    update_set_where();
    break;
  case 7: // CREATE INDEX AB
    create_index();
    break;
  case 8: // SELECT FROM WHERE AB
    select_from_where_ab();
    break;
  case 9: // INSERT INTO AB
    insert_into_ab();
    break;
  case 10: // DELETE FROM WHERE AB
    delete_from_where_ab();
    break;
  default:
    printf("Operação inválida.\n");
    break;
  }

  return 0;
}
