#include "filesystem.h"
#include "server.h"

#include <stddef.h>

int main (int argc, char **argv)
{
    // TEST
    char **file_list = NULL;
    unsigned int list_size = 0;
    generate_file_database (".", file_list, &list_size);
    // ENDTEST

    return 0;
}
