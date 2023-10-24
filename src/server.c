#include "server.h"


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
