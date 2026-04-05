#ifndef SQLFUNCTIONS_H
#define SQLFUNCTIONS_H

#include <stdbool.h>


// Create table
bool csv_to_bin(char *csv_name, char *bin_name);
bool select_from(char *bin_name);
bool select_from_where(char *bin_name);
bool delete_from_where(char *bin_name);
bool update_set_where(char *bin_name);


#endif
