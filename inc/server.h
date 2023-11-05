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

struct server_info
{
    // Network info
    char *host_ip;
    unsigned int port;

    // Program directories
    char *backup_directory, *data_directory;

    // Config and database files
    char *config_file, *file_database, *timestamp_database;
};

struct server_info *create_new_server();
void blank_init_server (struct server_info *);

#endif
