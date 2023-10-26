#include "list.h"

#include <stdlib.h>
#include <string.h>

struct string_list * create_string_list ()
{
    // Allocate memory for new list
    struct string_list *new_list = malloc (sizeof (struct string_list_member));

    // Set member variables to defaults
    new_list->head = new_list->tail = NULL;
    new_list->size = 0;

    return new_list;
}

struct string_list_member * create_string_list_member (char *input_string)
{
    // Allocate memory for list member and string data
    struct string_list_member *new_member = malloc (sizeof (struct string_list_member));
    new_member->c_string = malloc (strlen (input_string) * sizeof (char));
    strcpy (new_member->c_string, input_string);

    // Set NULL pointers for adjacent elements
    new_member->next = new_member->previous = NULL;

    return new_member;
}

void push_front_string_list (struct string_list *list, struct string_list_member *member)
{
    // List isn't empty, stitch new element in
    if (list->head != NULL)
    {
        member->next = list->head;
        list->head->previous = member;
        list->head = member;
    }
    // Assuming a NULL head means the list is empty, make node the head and tail
    else
    {
        list->head = list->tail = member;
    }
}

void push_back_string_list (struct string_list *list, struct string_list_member *member)
{
    // List isn't empty, stitch in new element
    if (list->tail != NULL)
    {
        member->previous = list->tail;
        list->tail->next = member;
        list->tail = member;
    }
    // Assuming a NULL tail means the list is empty, make node the head and tail
    else
    {
        list->head = list->tail = member;
    }
}
