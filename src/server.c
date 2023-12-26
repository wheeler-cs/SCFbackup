#include "server.h"

struct file_server *create_file_server()
{
    struct file_server *new_server = malloc (sizeof (struct file_server));

    // Init member vars to some defaults
    new_server->socket = -1;
    new_server->logging = NULL;
    new_server->context = NULL;
}

void initialize_logging (struct file_server *server_instance, char *log_file)
{
    if ((server_instance->logging = fopen (log_file, "a")) == NULL)
    {
        server_shutdown (server_instance, "Couldn't open log file for logging");
        exit (EXIT_FAILURE);
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
        server_shutdown (server_instance, "Unable to create new socket");
        exit (EXIT_FAILURE);
    }

    if ((bind (server_instance->socket, (struct sockaddr *) &new_socket, sizeof (new_socket))) < 0)
    {
        server_shutdown (server_instance, "Unable to bind socket to specified port");
        exit (EXIT_FAILURE);
    }

    if ((listen (server_instance->socket, 1)) < 0)
    {
        server_shutdown (server_instance, "Unable to listen in on newly-created socket");
        exit (EXIT_FAILURE);
    }
}

void initialize_context (struct file_server *server_instance)
{
    const SSL_METHOD *method = TLS_server_method();
    server_instance->context = SSL_CTX_new (method);

    if (!(server_instance->context))
    {
        server_shutdown (server_instance, "Couldn't create TLS context for connection");
        exit (EXIT_FAILURE);
    }

    // Load PEM files
    if (SSL_CTX_use_certificate_file (server_instance->context, "cert.pem", SSL_FILETYPE_PEM) <= 0)
    {
        server_shutdown (server_instance, "Unable to load certification PEM file");
        exit (EXIT_FAILURE);
    }
    if (SSL_CTX_use_PrivateKey_file (server_instance->context, "key.pem", SSL_FILETYPE_PEM) <= 0)
    {
        server_shutdown (server_instance, "Unable to load key PEM file");
        exit (EXIT_FAILURE);
    }
}

// =====================================================================================================================

void server_shutdown (struct file_server *server_instance, char *message)
{
    if (server_instance)
    {
        // Deallocate memory for member vars and set pointers to NULL
        if (server_instance->logging)
        {
            fclose (server_instance->logging);
            server_instance->logging = NULL;
        }
        if (server_instance->context)
        {
            SSL_CTX_free (server_instance->context);
            server_instance->context = NULL;
        }

        // Deallocate memory for server
        free (server_instance);
    }

    if (message)
        printf ("%s\n", message);
}

