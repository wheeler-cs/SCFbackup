#include "filesystem.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{

    struct file_index* test_idx = generate_file_index ("./src");
    traverse_print_index (test_idx);
    delete_index (test_idx);

    printf ("\n");
    return 0;
}
