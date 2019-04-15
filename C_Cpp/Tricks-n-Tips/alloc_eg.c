#include "alloc.h"

int main(int argc, char const *argv[])
{
    int *new_memory = MALLOC(25, int);
    // ...
    FREE(new_memory);
    return 0;
}
