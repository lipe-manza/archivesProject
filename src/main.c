#include <stdio.h>
#include "../include/sql_functions.h"
#include "../include/IO.h"

int main()
{
    int n = 0;

    // Lê o número da operação
    scanf("%d", &n);

    char bin_name[50] = "data/";

    switch (n)
    {
    case 1: // Create table
    {
        // Lê os
        char csv_name[50] = "data/";
        scanf("%s %s", csv_name + 5, bin_name + 5);

        bool success = csv_to_bin(csv_name, bin_name);

        if (success)
            BinarioNaTela(bin_name);

        break;
    }
    case 2: // SELECT FROM
    {
        scanf("%s", bin_name + 5);

        select_from(bin_name);

        break;
    }
    case 3: // SELECT FROM WHERE
    {
        scanf("%s", bin_name + 5);

        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; i++)
        {
            select_from_where(bin_name);
        }

        break;
    }
    case 4: // DELETE FROM WHERE
    {
        scanf("%s", bin_name + 5);

        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; i++)
        {
            delete_from_where(bin_name);
        }

        BinarioNaTela(bin_name);
        break;
    }
    case 5: // INSERT INTO
    {
        
        break;
    }
    case 6: // UPDATE SET WHERE
    {
        scanf("%s", bin_name + 5);

        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; i++)
        {
            update_set_where(bin_name);
        }

        BinarioNaTela(bin_name);

        break;
    }
    }

    return 0;
}
