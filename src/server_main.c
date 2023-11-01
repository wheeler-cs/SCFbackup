#include "filesystem.h"
#include "hash.h"
#include "list.h"
#include "server.h"

#include <stddef.h>
#include <stdio.h>

int main (int argc, char **argv)
{
    // TEST
    struct string_list *str_list = create_string_list();
    generate_file_database (".", str_list);
    printf ("Hash: %x", calculate_file_crc32 ("Makefile"));
    delete_string_list (&str_list);
    // ENDTEST

    return 0;
}
