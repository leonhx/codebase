/*
 * a safer memory allocation fucntion - implementation
 * usage: see alloc_eg.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "alloc.h"
#undef malloc

void *alloc(size_t size) {
    void *new_mem = malloc(size);
    if (new_mem == NULL) {
        fprintf(stderr, "Fatal: out of memory!\n");
        exit(EXIT_FAILURE);
    }
    return new_mem;
}
