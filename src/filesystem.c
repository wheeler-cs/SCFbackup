#include "filesystem.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// === Begin Linux Code ================================================================================================
#if defined(__linux__)
void generate_file_database (char *root_directory, struct data_list *file_list)
{
    DIR *dir_ptr;
    struct dirent *directory_info;
    struct stat file_info;

    char *full_name = NULL, *full_name_copy = NULL;
    unsigned int full_name_length = 0;

    struct list_member *database_insert;

    // Attempt to open directory for indexing
    if ((dir_ptr = opendir (root_directory)) != NULL)
    {
        // Read through directory and locate all files within
        while ((directory_info = readdir (dir_ptr)) != NULL)
        {
            // Ignore . and .. directories
            if (!(strcmp (directory_info->d_name, ".")) || !(strcmp (directory_info->d_name, "..")))
                continue;

            // Setup the full file's path to be opened
            full_name_length = strlen (root_directory) + strlen (directory_info->d_name) + 2; // Add 2 for '/' and '\0'
            full_name_copy = realloc (full_name, full_name_length * sizeof (char));
            // Sanity check memory reallocation
            if (full_name_copy == NULL)
            {
                fprintf (stderr, "\nUnable to allocate memory needed for directory database building.");
                void (*free_file_record) (struct file_record*) = &delete_file_record;
                delete_list (&file_list, (void (*) (void *)) free_file_record);
                free (full_name);
                return;
            }
            // Combine higher directories w/ file name into one C-string
            full_name = full_name_copy;
            memset (full_name, '\0', full_name_length * sizeof (char));
            strcat (full_name, root_directory);
            strcat (full_name, "/");
            strcat (full_name, directory_info->d_name);

            // Get the filesystem attributes of the file
            if ((stat (full_name, &file_info)) == 0)
            {
                if (S_ISDIR (file_info.st_mode)) // File is a directory, recurse
                {
                    generate_file_database (full_name, file_list);
                }
                else if (S_ISREG(file_info.st_mode)) // File is an actual file, add to list
                {
                    database_insert = create_list_member (sizeof (struct list_member));
                    database_insert->data = create_file_record (full_name, file_info.st_mtime);
                    push_front_list (file_list, database_insert);
                }
            }
        }

        // Stop a memory leak
        closedir (dir_ptr);
        free (full_name);
    }
    else
    {
        // TODO: Add better error handling for this
        fprintf (stderr, "\nCannot open directory");
    }
}

// === Begin Windows Code ==============================================================================================
#elif defined (__WIN32)
unsigned int generate_file_database (char *root_directory, char **file_names)
{

}

#endif

struct file_record *create_file_record (char *name, time_t mod_time)
{
    struct file_record *new_record = malloc (sizeof (struct file_record));
    new_record->file_name = malloc ((strlen (name) + 1) * sizeof (char));
    strcpy (new_record->file_name, name);
    new_record->modified_time = mod_time;

    return new_record;
}

void delete_file_record (struct file_record* del_record)
{
    free (del_record->file_name);
    free (del_record);
}
