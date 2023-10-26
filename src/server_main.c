#include "filesystem.h"
#include "list.h"
#include "server.h"

#include <stddef.h>
#include <stdio.h>

int main (int argc, char **argv)
{
    // TEST
    struct string_list *str_list = create_string_list();
    struct string_list_member *list_mem = create_string_list_member ("Hello, World!");
    push_front_string_list (str_list, list_mem);
    printf ("\nHead: %s", str_list->head->c_string);
    printf ("\nTail: %s", str_list->tail->c_string);
    printf ("\nList Status: %d", is_string_list_empty (str_list));
    delete_string_list (str_list);
    printf ("\nList Status: %d", is_string_list_empty (str_list));
    printf ("\n");
    // ENDTEST

    return 0;
}
