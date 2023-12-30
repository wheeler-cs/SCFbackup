#ifndef SCF_CLIENT_H
#define SCF_CLIENT_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <openssl/ssl.h>

struct file_client {
    char *remote_name;
    int remote_port;
    FILE *logging;
    SSL_CTX *context;
};

struct file_client *initialize_file_client();
void initialize_logging (struct file_client *, char *);
void initialize_socket (struct file_client *, int);
void initialize_context (struct file_client *);
void client_shutdown (struct file_client *, char *);

#endif
