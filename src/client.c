#include "client.h"

#include <openssl/err.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

struct file_client *initialize_file_client()
{
    struct file_client *new_client = malloc (sizeof (struct file_client));

    new_client->remote_name = NULL;
    new_client->remote_port = 0;
    new_client->logging = NULL;
    new_client->context = NULL;

    return new_client;
}

void initialize_logging (struct file_client *client_instance, char *log_file)
{
    if ((client_instance->logging = fopen (log_file, "a")) == NULL)
    {
        client_shutdown (client_instance, "Couldn't open log file for logging");
        exit (EXIT_FAILURE);
    }
}

void initialize_socket (struct file_client *client_instance, int port)
{

}

void initialize_context (struct file_client *client_instance)
{
    const SSL_METHOD *method = TLS_method();
    if (!method)
    {
        client_shutdown (client_instance, "Unable to create connection context");
        exit (EXIT_FAILURE);
    }

    client_instance->context = SSL_CTX_new (method);
}

void client_shutdown (struct file_client *client_instance, char *message)
{
    if (client_instance)
    {
        if (client_instance->logging)
        {
            fclose (client_instance->logging);
            client_instance->logging = NULL;
        }
        if (client_instance->context)
        {
            SSL_CTX_free (client_instance->context);
            client_instance->context = NULL;;
        }

        free (client_instance);
    }

    if (message)
        printf ("%s\n", message);
}
