/*
 * a safer memory allocation fucntion - header file
 * usage: see alloc_eg.c
 */

#include <stdlib.h>

#define malloc "DO NOT use **malloc**"
#define MALLOC(num, type) (type *)alloc((num) * sizeof(type))
#define FREE(p) free(p)

extern void *alloc(size_t size);
