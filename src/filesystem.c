#include "filesystem.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// === Begin Linux Code ================================================================================================
#if defined(__linux__)
struct file_index *generate_file_database (char *root_directory)
{



}

// === Begin Windows Code ==============================================================================================
#elif defined (__WIN32)
unsigned int generate_file_database (char *root_directory, char **file_names)
{

}

#endif

struct file_index *create_file_index()
{
    // Allocate memory and set defaut values
    struct file_index *new_ptr = (struct file_index *) malloc (sizeof (struct file_index));
    new_ptr->list_start = NULL;
    new_ptr->index_size = 0;

    return new_ptr;
}

void append_file_to_index (struct file_index *target, char *file_name)
{
    // Setup the require memory allocation for the new entry in the index
    struct file_entry *new_entry = (struct file_entry *) malloc (sizeof (struct file_entry));
    new_entry->file_name = (char *) malloc (sizeof (char) * (strlen (file_name) + 1));
    strcpy (new_entry->file_name, file_name);
    new_entry->next_file = NULL;

    // Append the entry to the index
    struct file_entry *current_tail = index_tail (target);
    if (current_tail == NULL) // List is empty, make entry the head
        target->list_start = new_entry;
    else
        current_tail->next_file = new_entry;

    // Increase the counter for the index
    ++(target->index_size);

}

struct file_entry *index_tail (struct file_index *target)
{

    struct file_entry *idx_ptr = target->list_start;

    if (idx_ptr == NULL) // List is empty, don't bother with the algorithm
        return NULL;
    
    while (idx_ptr->next_file != NULL) // Loop through until the tail is found
        idx_ptr = idx_ptr->next_file;

    return idx_ptr;

}

void traverse_print_index (struct file_index *input)
{
    struct file_entry *idx_ptr = input->list_start;

    while (idx_ptr != NULL)
    {
        printf ("%s\n", idx_ptr->file_name);
        idx_ptr = idx_ptr->next_file;
    }
}

void delete_index (struct file_index *target)
{
    struct file_entry *deleted_entry = target->list_start,
                      *next_entry = NULL;

    while (deleted_entry != NULL)
    {
        next_entry = deleted_entry->next_file;
        free (deleted_entry->file_name);
        free (deleted_entry);
        deleted_entry = next_entry;
    }

    free (target);
    target = NULL;
}
