#include "filesystem.h"
#include "server.h"

#include <stddef.h>

int main (int argc, char **argv)
{
    // TEST
    char **dummy_buffer = NULL;
    generate_file_database (".", dummy_buffer);
    // ENDTEST

    return 0;
}
