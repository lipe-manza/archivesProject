#include <stdio.h>
#include "../include/csv_to_bin.h"
#include "../include/read_bin.h"
#include "../include/fornecidas.h"

int main()
{
    int n = 0;

    scanf("%d", &n);

    char bin_name[50];
    switch (n)
    {
        case 1: // Create table
        {
            // Variaveis de ajuda
            char csv[50];

            scanf(" %s %s ", csv , bin_name);
            FILE *p_bin;

            if (csv_to_bin(csv, bin_name))
                BinarioNaTela(bin_name);

            break;
        }
        case 2: // SELECT FROM
        {

            scanf(" %s ", bin_name);

            if(select_from(bin_name))
                BinarioNaTela(bin_name);

            break;
        }
        case 3: // SELECT FROM WHERE
        {
            scanf(" %s ", bin_name);

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
            break;
        }
        case 5: // INSERT INTO
        {
            break;
        }
        case 6: // UPDATE SET WHERE
        {
            break;
        }
    }
}
