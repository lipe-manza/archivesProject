// Luiz Felipe Manzoli Franceschini - 16913300
// Enzo Trulenque Evangelista - 15819219

#include <stdio.h>
#include "sql_functions.h"
#include "IO.h"

int main()
{
    int n = 0;

    // Lê o número da operação
    if (scanf("%d", &n) != 1)
        return 0;

    switch (n)
    {
    case 1: // Create table
        csv_to_bin();
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
        insert_from_where();
        break;
    case 6: // UPDATE SET WHERE
        update_set_where();
        break;
    }

    return 0;
}
