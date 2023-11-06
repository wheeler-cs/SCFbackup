#include "filesystem.h"
#include "list.h"
#include "server.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    // TEST
    struct server_info *storage_server = create_new_server();
    storage_server->data_directory = ".";
    generate_file_database (storage_server->data_directory, storage_server->file_data);
    delete_server (&storage_server, (void (*) (void*)) delete_file_record);
    // ENDTEST

    printf ("\n");
    return 0;
}
