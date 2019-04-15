/*
 * string literal
 */

#include <stdio.h>

/*
 * Guess what `mystery` does? And why?
 */
void mystery (int n) {
    n += 5;
    n /= 10;
    printf("%s\n", "***********" + 10 - n%10);
}
/*
 * The key is that string literal returns the pointer to the first
 * character of the string.
 *
 * Think about the example above: how you might do if you are asked
 * to implement it using `for` or `while` loop
 */

/* remind this: */
 char *str = "This is a string";
/* This is it. */

/* Then you can understand what the following means: */
putchar("0123456789ABCDEF" [value % 16]);
