#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Allocates the memory for a new string_list object and sets default values for its member variables.
 * 
 * @returns The address of the newly-allocated string_list object.
 * 
 * @post Memory is allocated from the heap for the new struct instance and provided to the calling function as a
 *       pointer.
 * 
 */
struct string_list *create_string_list ()
{
    // Allocate memory for new list
    struct string_list *new_list = malloc (sizeof (struct string_list));

    // Set member variables to defaults
    new_list->head = new_list->tail = NULL;
    new_list->size = 0;

    return new_list;
}

/**
 * @brief Iterates through a string_list instance, removing each element until the list is empty.
 * 
 * @param list Pointer of a pointer to a string_list instance.
 * 
 * @pre It is expected that the list parameter has been allocated at least the memory required for a blank string_list.
 * @post All allocated memory for the string_list object, including memory of its members, is deallocated, and the
 *       dangling pointer it leaves behind is set to NULL.
 * 
 * @see delete_string_list_member
 * 
*/
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

/**
 * @brief Allocates the memory needed for a string_list_member, based on the given input string.
 * 
 * @param input_string A C-string containing the characters the newly initialized string_list_member will store.
 * 
 * @returns A pointer to the newly-allocated string_list_member.
 * 
 * @post Memory is allocated for both the new string_list_member and its c_string member variable.
 * 
*/
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

/**
 * @brief Frees up the memory allocated by the creation of the string_list_member instance.
 * 
 * @param member Pointer to an initialized instance of the string_list_member struct.
 *
 * @pre It is expected that the member parameter points to a properly-initialized string_list_member.
 * @post Memory allocated to the given string_list_member instance is deallocated completely.
 * 
 * @note The dangling pointer is not handled in this function call and must be done so outside of it.
 * 
*/
void delete_string_list_member (struct string_list_member *member)
{
    // Clean up memory allocated for member and its string
    // FIX: Memory leak was caused her originally because c_string data wasn't being freed w/ string_list_member.
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
