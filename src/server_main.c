#include "filesystem.h"
#include "server.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    struct file_server *test_srvr = initialize_file_server();
    initialize_logging (test_srvr, "server.log");
    initialize_socket (test_srvr, 9000);
    initialize_context (test_srvr);
    run_server (test_srvr);

    /*
    struct file_index* test_idx = generate_file_index ("./src");
    traverse_print_index (test_idx);
    delete_index (test_idx);
    */

    printf ("\n");
    return 0;
}
