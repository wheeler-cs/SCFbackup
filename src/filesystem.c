#include "filesystem.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#if defined(__linux__)
unsigned int generate_file_database (char *root_directory, char **file_names)
{
    DIR *dir_ptr;
    struct dirent *directory_info;
    struct stat file_info;

    // Attempt to open directory for indexing
    if ((dir_ptr = opendir (root_directory)) != NULL)
    {
        while ((directory_info = readdir (dir_ptr)) != NULL)
        {
            // Ignore . and .. directories
            if ((abs (strcmp (directory_info->d_name, "."))) ||
                (abs (strcmp (directory_info->d_name, ".."))))
                continue;


        }

        // Stop a memory leak
        closedir (dir_ptr);
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
