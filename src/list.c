#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct string_list *create_string_list ()
{
    // Allocate memory for new list
    struct string_list *new_list = malloc (sizeof (struct string_list_member));

    // Set member variables to defaults
    new_list->head = new_list->tail = NULL;
    new_list->size = 0;

    return new_list;
}

void delete_string_list (struct string_list **list)
{
    struct string_list_member *traverser;

    // Linearly iterate through list and pop off the head until the list is empty
    while ((traverser = pop_front_string_list (*list)) != NULL)
    {
        delete_string_list_member (traverser);
    }

    free (*list);
    *list = NULL; // Clean up dangling pointer
}

struct string_list_member *create_string_list_member (char *input_string)
{
    // Allocate memory for list member and string data
    struct string_list_member *new_member = malloc (sizeof (struct string_list_member));
    new_member->c_string = malloc ((strlen (input_string) + 1) * sizeof (char));
    strcpy (new_member->c_string, input_string);

    // Set NULL pointers for adjacent elements
    new_member->next = new_member->previous = NULL;

    return new_member;
}

void delete_string_list_member (struct string_list_member *member)
{
    // Clean up memory allocated for member and its string
    free (member->c_string);
    free (member);
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

    ++(list->size);
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

    ++(list->size);
}

struct string_list_member *pop_front_string_list (struct string_list *list)
{
    struct string_list_member *popped_member;

    // List still has elements in it, pop front
    if (list->head != NULL)
    {
        popped_member = list->head;

        // Popping will result in an empty list
        if (list->head->next == NULL)
            list->head = list->tail = NULL;
        // List will still have elements after operation
        else
        {
            list->head = list->head->next;
            list->head->previous = NULL;
        }

        // Sever member's connection to other elements, regardless of the list's status
        popped_member->next = popped_member->previous = NULL;

        --(list->size);
    }
    // List is empty, return NULL
    else
        return NULL;

    return popped_member;
}

struct string_list_member *pop_back_string_list (struct string_list *list)
{
    struct string_list_member *popped_member;

    // List still has elements in it, pop back
    if (list->tail != NULL)
    {
        popped_member = list->tail;

        // Popping will result in an empty list
        if (list->tail->previous == NULL)
            list->head = list->tail = NULL;
        // List will still have elements after operation
        else
        {
            list->tail = list->tail->previous;
            list->tail->next = NULL;
        }

        // Sever member's connection to other elements, regardless of the list's status
        popped_member->next = popped_member->previous = NULL;

        --(list->size);
    }
    // List is empty, return NULL
    else
        return NULL;

    return popped_member;
}

int is_string_list_empty (struct string_list *list)
{
    if (list == NULL)
        return 1;
    else if ((list->head == NULL) && (list->tail == NULL))
        return 1;
    else
        return 0;
}

int is_string_list_malformed (struct string_list *list)
{
    // Head and tail both either need to point to NULL or to some non-NULL address, not a mix
    if (((list->head == NULL) && (list->tail != NULL)) ||
        ((list->head != NULL) && (list->tail == NULL)))
        return 1;
    else
        return 0;
}
