/*
 * string
 */

#include <string.h>

char buffer[BSIZE];
// ...
// char *strncpy(char *dst, char const *src, size_t len);
strncpy(buffer, name, BSIZE); // `strncpy` does NOT ensure the dst string
buffer[BSIZE-1] = '\0'; // ending up with NUL when size of the src string
                        // exceeds len
