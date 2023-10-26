#include "filesystem.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#if defined(__linux__)
void generate_file_database (char *root_directory, char **file_names, unsigned int *list_size)
{
    DIR *dir_ptr;
    struct dirent *directory_info;
    struct stat file_info;

    char *full_name = NULL, *full_name_copy = NULL;
    unsigned int full_name_length = 0;
    char **file_names_copy = NULL;

    // Attempt to open directory for indexing
    if ((dir_ptr = opendir (root_directory)) != NULL)
    {
        while ((directory_info = readdir (dir_ptr)) != NULL)
        {
            // Ignore . and .. directories
            if (!(strcmp (directory_info->d_name, ".")) || !(strcmp (directory_info->d_name, "..")))
                continue;

            // NOTE: This is kind a jank way of doing it
            // TODO: Make this better in the future
            full_name_length = strlen (root_directory) + 1 + strlen (directory_info->d_name);
            full_name_copy = realloc (full_name, full_name_length * sizeof (char));
            if (full_name_copy == NULL)
            {
                fprintf (stderr, "\nUnable to allocate memory for file name.");
                free (full_name);
                return;
            }
            full_name = full_name_copy;
            memset (full_name, '\0', full_name_length * sizeof (char));
            strcat (full_name, root_directory);
            strcat (full_name, "/");
            strcat (full_name, directory_info->d_name);
            printf ("\n%s", full_name);

            // Get the filesystem attributes of the file
            if ((stat (full_name, &file_info)) == 0)
            {
                if (S_ISDIR (file_info.st_mode)) // File is a directory, recurse
                {
                    printf ("/");
                    generate_file_database (full_name, file_names, list_size);
                }
                else if (S_ISREG(file_info.st_mode)) // File is an actual file, add to list
                {
                    printf ("**");
                    *list_size = *list_size + 1;
                    printf ("\nAllocating memory to list.");
                    file_names_copy = realloc (file_names, *list_size * sizeof (char*));
                    if (file_names_copy == NULL)
                    {
                        fprintf (stderr, "\nUnable to allocate memory for file entry list.");
                        free (file_names);
                        return;
                    }

                    file_names = file_names_copy;

                }
            }
        }

        // Stop a memory leak
        closedir (dir_ptr);
        free (full_name);
        printf ("\n");
    }
    else
    {
        fprintf (stderr, "Cannot open directory");
    }
}
/*

        std::string full_path = "";
        while ((dir_entity = readdir (dir_ptr)) != NULL)
        {
            full_path = input_dir + '/' + dir_entity->d_name;
            
            if (stat (full_path.c_str(), &f_info) == 0)
            {
                // Recurse using gen_dir_index again if path refers to directory
                if (f_info.st_mode & S_IFDIR)
                {
                    gen_dir_index (full_path, dir_index);
                }
                // Add path to list if refers to file
                else if (f_info.st_mode & S_IFREG)
                {
                    dir_index.push_back (File(full_path));
                }
            }
        }
    }

    return dir_index.size();
}
*/
#elif defined (__WIN32)
unsigned int generate_file_database (char *root_directory, char **file_names)
{

}

#endif
