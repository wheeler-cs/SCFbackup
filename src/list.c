#include "list.h"

#include "filesystem.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Allocates the memory for a new data_list object and sets default values for its member variables.
 * 
 * @returns The address of the newly-allocated data_list object.
 * 
 * @post Memory is allocated from the heap for the new struct instance and provided to the calling function as a
 *       pointer.
 * 
 */
struct data_list *create_list ()
{
    // Allocate memory for new list
    struct data_list *new_list = malloc (sizeof (struct data_list));

    // Set member variables to defaults
    new_list->head = new_list->tail = NULL;
    new_list->size = 0;

    return new_list;
}

/**
 * @brief Iterates through a data_list instance, removing each element until the list is empty.
 * 
 * @param list Pointer of a pointer to a data_list instance.
 * 
 * @pre It is expected that the list parameter has been allocated at least the memory required for a blank data_list.
 * @post All allocated memory for the data_list object, including memory of its members, is deallocated, and the
 *       dangling pointer it leaves behind is set to NULL.
 * 
 * @see delete_data_list_member
 * 
*/
void delete_list (struct data_list **list, void (*f) (void *))
{
    struct list_member *traverser;

    // Linearly iterate through list and pop off the head until the list is empty
    while ((traverser = pop_front_list (*list)) != NULL)
    {
        delete_list_member (traverser, f);
    }

    free (*list);
    *list = NULL; // Clean up dangling pointer
}

/**
 * @brief Allocates the memory needed for a list_member, based on a given data_size.
 * 
 * @param data_size The size of the data type to be associated with the newly-allocated list_member.
 * 
 * @returns A pointer to the newly-allocated list_member.
 * 
 * @post Memory is allocated for both the new list_member and its data member variable.
 * 
*/
struct list_member *create_list_member (unsigned int data_size)
{
    // Allocate memory for list member and associated data
    struct list_member *new_member = malloc (sizeof (struct list_member));
    new_member->data_size = data_size;

    // Set NULL pointers for adjacent elements
    new_member->next = new_member->previous = NULL;

    return new_member;
}

/**
 * @brief Frees up the memory allocated by the creation of the list_member instance.
 * 
 * @param member Pointer to an initialized instance of the list_member struct.
 *
 * @pre It is expected that the member parameter points to a properly-initialized list_member.
 * @post Memory allocated to the given list_member instance is deallocated completely.
 * 
 * @note The dangling pointer is not handled in this function call and must be done so outside of it.
 * 
*/
void delete_list_member (struct list_member *member, void (*f) (void *))
{
     if (f == NULL) // Basic data, no special dealloc function needed
     {
        free (member->data);
     }
    else // Special data type (e.g. struct) needs special dealloc function
    {
        f (member->data);
    }
    free (member);
}

/**
 * @brief Adds a list_member to the front of a data_list instance.
 * 
 * @param list Destination data_list instance for the list_member.
 * @param member The list_member to be inserted at the front of the list.
 * 
 * @pre Both parameters have been properly allocated and initialized.
 * @post The member parameter is the new head of the list parameter.
 * 
 * @note If the list instance is empty, head and tail are both set to point to the member paramter.
 * 
*/
void push_front_list (struct data_list *list, struct list_member *member)
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

/**
 * @brief Adds a list_member to the back of a data_list instance.
 * 
 * @param list Destination data_list instance for the list_member.
 * @param member The list_member_to be inserted at the rear of the list.
 * 
 * @pre Both parameters have been properly allocated and initialized.
 * @post The member parameter is the new tail of the list paramter.
 * 
 * @note If the list instance is empty, head and tail are both set to point to the member paramter.
 * 
*/
void push_back_list (struct data_list *list, struct list_member *member)
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

/**
 * @brief Removes the head list_member from a data_list instance.
 * 
 * @param list Source list from which the head element will be popped off.
 * 
 * @returns The list_member that was popped from the front of the parameter list.
 * @retval NULL indicates that the list was empty and no member could be popped from the front.
 * 
 * @post If the list parameter was not empty, the head element is popped and the next element in the sequence is set to
 *       be the new head.
 * 
 * @note If the element being popped from the list is the last one, both the head and tail pointers of the data_list
 *       are set to NULL.
 * 
*/
struct list_member *pop_front_list (struct data_list *list)
{
    struct list_member *popped_member;

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

/**
 * @brief Removes the tail list_member from a data_list instance.
 * 
 * @param list Source list from which the tail will be popped off.
 * 
 * @returns The list_member that was popped from the back of the parameter list.
 * @retval NULL indicates that the list was empty and no member could be popped from the rear.
 * 
 * @post If the list parameter was not empty, the tail element is popped and the previous element in the sequence is set
 *       to be the new tail
 *
 * @note If the element being popped from the list is the last one, both the head and tail pointers of the data_list
 *       are set to NULL.
 * 
*/
struct list_member *pop_back_list (struct data_list *list)
{
    struct list_member *popped_member;

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

/**
 * @brief Returns if the data_list is empty or not.
 * 
 * @param list The list to be evaluated for if it has member elements.
 * 
 * @returns The state of the list being empty or not empty.
 * @retval 0 indicates the list is not empty.
 * @retval 1 indicates the list is empty.
 * 
 * @note A list will be indicated as empty if the pointer itself is NULL or both the head and tail pointers are NULL.
 * 
*/
int is_list_empty (struct data_list *list)
{
    if (list == NULL)
        return 1;
    else if ((list->head == NULL) && (list->tail == NULL))
        return 1;
    else
        return 0;
}

/**
 * @brief Returns if the data_list is in a valid state.
 * 
 * @param list The list to be checked for if it is in a valid state.
 * 
 * @returns The state of the list's validity.
 * @retval 0 indicates list is well-formed and can continue to be used.
 * @retval 1 indicates the head and tail pointers are mismatched such that one is NULL and the other is not.
 * 
*/
int is_list_malformed (struct data_list *list)
{
    // Head and tail both either need to point to NULL or to some non-NULL address, not a mix
    if (((list->head == NULL) && (list->tail != NULL)) || ((list->head != NULL) && (list->tail == NULL)))
        return 1;
    else
        return 0;
}
