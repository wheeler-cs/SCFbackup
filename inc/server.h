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

#include <stdint.h>

struct server_network
{
    char *ip_address;
    unsigned int port;
};


struct server_config
{
    char *backup_dir, *data_dir;
    char *config_file, *file_database;
};


struct server_info
{
    struct server_network networking;
    struct server_config configuration;

    // File data
    struct data_list *file_data;
};


struct server_info *create_new_server();
void blank_init_server (struct server_info *);
void delete_server_data (struct server_info**, void (*) (void*));

#endif
