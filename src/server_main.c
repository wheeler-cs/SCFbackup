#include "filesystem.h"
#include "hash.h"
#include "list.h"
#include "server.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    // TEST
    struct data_list *dat_list = create_list();
    generate_file_database ("inc", dat_list);
    delete_list (&dat_list, (void (*) (void *)) &delete_file_record);
    if (is_list_empty (dat_list))
        printf ("\nData list is empty");
    printf ("\n");
    // ENDTEST

    return 0;
}
