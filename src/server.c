#include "filesystem.h"
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
    server_instance->networking.ip_address = "127.0.0.1";
    server_instance->networking.port = 8080;

    // Directories required for server to run
    server_instance->configuration.backup_dir = "backup";
    server_instance->configuration.data_dir = "data";

    // Required files for server; found in data_directory
    server_instance->configuration.config_file = "server.cfg";
    server_instance->configuration.file_database = "database.json";

    // Set up server's data list used to track files
    server_instance->file_data = create_list();
}

/**
 * @brief Properly deallocates all memory acquired by an instance of server_info.
 *
 * @param server_info Pointer to the server_info instance that will have all containing memory
 *        deallocated.
 * @param f Pointer to a deallocation function coded to handle the unique datatype store in the
 *        members of the instance's file_data.
 * @pre The server provided should be properly initialized and, ideally, have members contained
 *      within its file_data.
 * @post The instance of server_info is deallocated entirely, including sub-member data.
 *
 * @note The deallocation function f should take one argument: a pointer to the datatype it is
 *       designed to deallocate. From there, the function should properly deallocate the memory
 *       allocated for that instance.
 *
 * @see delete_file_record in filesystem.c for an example of f.
 */
void delete_server_data (struct server_info** server_instance, void (*f) (void*))
{
    // This is some REALLY gnarly code, the address of a dereferenced pointer to a pointer's
    // file_data; I did this primarily because I wanted to be able to handle the dangling pointer
    // pointer, not that it matters too awful much...
    delete_list (&(*server_instance)->file_data, f);
    free ((*server_instance)->file_data);
    free (*server_instance);

    // Handle the dangling pointer
    server_instance = NULL;
}
