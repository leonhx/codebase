/*
 * EXIT STATUS
 *
 * `EXIT_SUCCESS` and `EXIT_FAILURE` are defined
 * in `stdlib.h`
 */

#include <stdlib.h>

int foo()
{
    return EXIT_SUCCESS;
}

int bar()
{
    return EXIT_FAILURE;
}

int main(int argc, char const *argv[])
{
    foo();
    bar();
    return 0;
}
