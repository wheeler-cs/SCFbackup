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
    struct file_index *new_ptr = (struct file_index *) malloc (sizeof (struct file_index));
    new_ptr->list_start = NULL;
    new_ptr->index_size = 0;

    return new_ptr;
}

void append_file_to_index (struct file_index *target, char *file_name)
{

    struct file_entry *new_entry = (struct file_entry *) malloc (sizeof (struct file_entry));
    new_entry->file_name = (char *) malloc (sizeof (char) * strlen (file_name));
    memcpy (new_entry->file_name, file_name, strlen (file_name));
    new_entry->next_file = NULL;

    if (target->list_start == NULL)
        target->list_start = new_entry;
    else
    {
        // TODO: Traverse the index to get the last entry and append the new entry after that
    }

    ++(target->index_size);

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
