#include "filesystem.h"
#include "list.h"
#include "server.h"

#include <stddef.h>
#include <stdio.h>

int main (int argc, char **argv)
{
    // TEST
    struct string_list *str_list = create_string_list();
    generate_file_database (".", str_list, 3);
    traverse_print_string_list (str_list);
    delete_string_list (&str_list);
    // ENDTEST

    return 0;
}
