#include "filesystem.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// === Begin Linux Code ================================================================================================
#if defined(__linux__)
struct file_index *generate_file_index (char *root_directory)
{
    DIR *directory;
    struct dirent *directory_info;
    struct stat file_info;
    struct file_index *new_idx = create_file_index();

     if ((directory = opendir (root_directory)) != NULL)
     {
        char *full_file_name = malloc (strlen (root_directory));
        unsigned int full_name_size = 0;
        while ((directory_info = readdir (directory)) != NULL)
        {
            if (!(strcmp (directory_info->d_name, ".")) || !(strcmp (directory_info->d_name, ".."))) // Ignore . and ..
                continue;

            full_name_size = (strlen (root_directory) + strlen (directory_info->d_name) + 2);
            if ((full_file_name = (char *) realloc (full_file_name, full_name_size * sizeof (char))) == NULL)
            {
                // TODO: Do some actual error handling here, not just trying to go to the next iteration of the loop
                continue;
            }
            memset (full_file_name, '\0', full_name_size);
            strcat (full_file_name, root_directory);
            strcat (full_file_name, "/");
            strcat (full_file_name, directory_info->d_name);

            if ((stat (full_file_name, &file_info)) == 0)
            {
                if (S_ISDIR (file_info.st_mode)) // Refers to a directory, not a file
                {
                    merge_file_indices (new_idx, generate_file_index (full_file_name));
                }
                else if (S_ISREG (file_info.st_mode)) // Refers to a file
                {
                    append_file_to_index (new_idx, full_file_name);
                }
            }
        }

        closedir (directory);
        free (full_file_name);
     }

     return new_idx;
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

void merge_file_indices (struct file_index *destination, struct file_index *source)
{
    struct file_entry *dest_tail = index_tail (destination);

    dest_tail->next_file = source->list_start;
    source->list_start = NULL;
    delete_index (source);
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
