/**
 * @file server.h
 * @author wheeler-cs
 *
 * @brief Handles core functionality of the server, borrowing from other modules when needed.
 *
 * # TODO: Expand upon file description once development is further along.
 *
 */

#ifndef SCF_SERVER_H
#define SCF_SERVER_H

#include "list.h"

struct server_info
{
    // Network info
    char *host_ip;
    unsigned int port;

    // Program directories
    char *backup_directory, *data_directory;

    // Config and database files
    char *config_file, *file_database;

    // File data
    struct data_list *file_data;
};

struct server_info *create_new_server();
void blank_init_server (struct server_info *);
void delete_server (struct server_info**, void (*) (void*));

#endif
