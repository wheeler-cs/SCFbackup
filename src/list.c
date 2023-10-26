#include "list.h"

#include <stdlib.h>

struct string_linked_list * create_string_linked_list ()
{
    // Allocate memory for new list
    struct string_linked_list *new_list = malloc (sizeof (struct string_list_member));

    // Set member variables to defaults
    new_list->head = new_list->tail = NULL;
    new_list->size = 0;

    return new_list;
}
