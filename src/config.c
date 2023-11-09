#include "config.h"

#include <stdio.h>

void load_server_config (struct server_info *server_instance)
{
    FILE *config_read;

    if ((config_read = fopen (server_instance->configuration.config_file, "r")) == NULL)
    {
        fprintf (stderr, "\nUnable to load server configuration file. Creating file and loading defaults.");
    }
}
