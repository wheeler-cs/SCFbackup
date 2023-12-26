#include "filesystem.h"
#include "server.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    struct file_server *test_srvr = create_file_server();
    initialize_logging (test_srvr, "server.log");
    create_socket (test_srvr, 9000);
    initialize_context (test_srvr);
    server_shutdown (test_srvr, "Shutting down server");

    /*
    struct file_index* test_idx = generate_file_index ("./src");
    traverse_print_index (test_idx);
    delete_index (test_idx);
    */

    printf ("\n");
    return 0;
}
