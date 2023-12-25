#include "server.h"

struct file_server *create_file_server()
{
    struct file_server *new_server = malloc (sizeof (struct file_server));

    new_server->socket = -1;
    new_server->logging = NULL;
}

void initialize_logging (struct file_server *server_instance, char *log_file)
{
    if ((server_instance->logging = fopen (log_file, "a")) == NULL)
    {
        // Logging couldn't be initialized, exit the program
    }
}

// === Code in this block is based on https://wiki.openssl.org/index.php/Simple_TLS_Server =============================

void create_socket (struct file_server *server_instance, int port)
{
    // Set up socket for creation
    struct sockaddr_in new_socket;
    new_socket.sin_family = AF_INET;
    new_socket.sin_port = htons (port);
    new_socket.sin_addr.s_addr = htonl (INADDR_ANY);

    // Attempt to create a socket object and give it to the server
    if ((server_instance->socket = socket (AF_INET, SOCK_STREAM, 0)) < 0)
    {
        // Couldn't create the socket, exit the program
    }

    if ((bind (server_instance->socket, (struct sockaddr *) &new_socket, sizeof (new_socket))) < 0)
    {
        // Couldn't bind the socket, exit the program
    }

    if ((listen (server_instance->socket, 1)) < 0)
    {
        // Couldn't listen on the socket, exit the program
    }
}

void create_context (struct file_server *server_instance)
{
    const SSL_METHOD *method = TLS_server_method();
    server_instance->context = SSL_CTX_new (method);

    if (!(server_instance->context))
    {
        // Couldn't create TLS context, exit the program
    }
}

// =====================================================================================================================
