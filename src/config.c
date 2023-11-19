#include "config.h"


void load_server_config (struct server_info *server_instance)
{
    FILE *config_read;
    char file_line [128];

    if ((config_read = fopen (server_instance->configuration.config_file, "r")) == NULL)
    {
        fprintf (stderr, "\nUnable to load server configuration file. Creating file and loading defaults.");
    }
    else
    {
        // Read lines until that can't be done
        while ((fgets (file_line, sizeof file_line, config_read)) != NULL)
        {
            printf ("\n%s", file_line);
            if (feof (config_read)) // End of file has been reached
            {
                fclose (config_read);
                break;
            }

            if (file_line == "[directories]")
            {
                load_server_directories_config (server_instance, config_read);
            }
            else if (file_line == "[files]")
            {
                load_server_files_config (server_instance, config_read);
            }
            else if (file_line == "[network]")
            {
                load_server_network_config (server_instance, config_read);
            }
            else
            {
                fprintf (stderr, "\nUnrecognized line in server configuration: %s", file_line);
            }
        }
    }
}

void load_server_directories_config (struct server_info *server_instance, FILE *config_read)
{
    char file_line[128];

    while ((fgets (file_line, sizeof (file_line), config_read)) != NULL)
    {
        if (feof (config_read))
            break;

    }
}

void load_server_files_config (struct server_info * server_instance, FILE *config_read)
{
    char file_line[128];

    while ((fgets (file_line, sizeof (file_line), config_read)) != NULL)
    {
        if (feof (config_read))
            break;

    }
}

void load_server_network_config (struct server_info * server_instance, FILE *config_read)
{

    char file_line[128];

    while ((fgets (file_line, sizeof (file_line), config_read)) != NULL)
    {
        if (feof (config_read))
            break;

    }
}

