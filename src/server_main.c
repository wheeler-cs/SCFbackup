#include "filesystem.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{

    struct file_index* test_idx = create_file_index();
    append_file_to_index (test_idx, "TestA");
    append_file_to_index (test_idx, "TestB");
    append_file_to_index (test_idx, "TestC");
    delete_index (test_idx);

    printf ("\n");
    return 0;
}
