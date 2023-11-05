#include "server.h"

#include <stdlib.h>

/**
 * @brief Allocates the memory required for a new instance of the server_info struct.
 * 
 * @returns A pointer to the newly-allocated memory used for the server_info instance.
 * 
 * @post Memory is allocated for the server_info, which should be deallocated before program
 * termination.
*/
struct server_info *create_new_server()
{
    struct server_info *new_server_instance = malloc (sizeof (struct server_info));
    blank_init_server (new_server_instance); // Set default values so instance isn't empty.
    return new_server_instance;
}

/**
 * @brief Initializes internal information state for a server to a basic default. Used to prevent
 * accidental access of uninitialized variables for a server_info instance.
 *
 * @param server_instance The internal server state to be initialized.
 *
 * @pre server_instance points to a valid memory address that references a server_info object.
 * @post server_instance has a set of know default values for its member variables.
 *
*/
void blank_init_server (struct server_info *server_instance)
{
    // Network information for server
    server_instance->host_ip = "127.0.0.1";
    server_instance->port = 8080;

    // Directories required for server to run
    server_instance->backup_directory = "backup";
    server_instance->data_directory = "data";

    // Required files for server; found in data_directory
    server_instance->config_file = "server.cfg";
    server_instance->file_database = "database.json";
    server_instance->timestamp_database = "most_recent.json";
}
