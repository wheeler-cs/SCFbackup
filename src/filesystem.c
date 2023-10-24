#include "filesystem.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#if defined(__linux__)
unsigned int generate_file_database (char *root_directory, char **file_names)
{
    DIR *dir_ptr;
    struct dirent *directory_info;
    struct stat file_info;

    char *full_name = NULL;
    unsigned int full_name_length = 0;

    // Attempt to open directory for indexing
    if ((dir_ptr = opendir (root_directory)) != NULL)
    {
        while ((directory_info = readdir (dir_ptr)) != NULL)
        {
            // Ignore . and .. directories
            if (!(abs (strcmp (directory_info->d_name, "."))) ||
                !(abs (strcmp (directory_info->d_name, ".."))))
                continue;

            // NOTE: This is kind a jank way of doing it
            // TODO: Make this better in the future
            full_name_length = strlen (root_directory) + 1 + strlen (directory_info->d_name);
            full_name = malloc (full_name_length);
            memset (full_name, '\0', full_name_length * sizeof (char));
            strcat (full_name, root_directory);
            strcat (full_name, "/");
            strcat (full_name, directory_info->d_name);
            printf ("\n%s", full_name);


            if ((stat (full_name, &file_info)) == 0)
            {
                if (S_IFDIR (file_info.st_mode))
                {
                    printf ("\nDirectory Found!");
                    //generate_file_database (full_name, NULL);
                }
                else if (S_IFREG(file_info.st_mode))
                {
                    printf ("\nFile Found!");
                }
            }

            free (full_name);
        }

        // Stop a memory leak
        closedir (dir_ptr);
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
