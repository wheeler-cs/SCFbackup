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
    struct string_list_member *list_mem_2;
    push_front_string_list (str_list, list_mem);
    printf ("\nHead: %s", str_list->head->c_string);
    printf ("\nTail: %s", str_list->tail->c_string);
    list_mem_2 = pop_back_string_list (str_list);
    if ((str_list->head == NULL) && (str_list->tail == NULL))
        printf ("\nList is empty");
    printf ("\nValue: %s", list_mem_2->c_string);
    printf ("\n");
    // ENDTEST

    return 0;
}
