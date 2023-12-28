/**
 * @file server.h
 * @author wheeler-cs
 *
 * @brief Handles core functionality of the server, borrowing from other modules when needed.
 *
 *
 */
#ifndef SCF_SERVER_H
#define SCF_SERVER_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <openssl/ssl.h>

struct file_server {
    int socket, client;
    FILE *logging;
    SSL_CTX *context;
};


// Initialization functions
struct file_server *initialize_file_server();
void initialize_logging (struct file_server *, char *);
void initialize_socket (struct file_server *, int);
void initialize_context (struct file_server *);

// Server operation functions
void run_server (struct file_server *);
void shutdown_server (struct file_server *, char *);
void log_server (struct file_server *, char *, int);

#endif
