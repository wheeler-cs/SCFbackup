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
    char *host_ip;
    unsigned int port;

    char *backup_directory, *data_directory;

    char *config_file, *file_database, *timestamp_database;
};


void blank_init_server (struct server_info *);

#endif
