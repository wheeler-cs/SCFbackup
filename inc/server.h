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

#include <arpa/inet.h>
#include <sys/socket.h>
#include <openssl/ssl.h>

struct file_server {
    int socket;
    FILE *logging;
};


void create_socket (struct file_server *, int);
void initialize_logging (struct file_server *, char *);
struct file_server *create_file_server();

#endif
