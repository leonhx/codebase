/*
 * command-line options
 *
 * for example, we will use the program this way:
 * ```rocket_to -e 4 -a Brasilia Tokyo London```
 * of which the two options `e` and `a` stands for:
 * use four engines, awesomeness mode enabled, respectively
 */

#include <unistd.h>

int main(int argc, char const *argv[])
{
    while ((ch = getopt(argc, argv, "ae:")) != EOF)
        // "ae:" means The a option is valid; so is the e option
        // The “:” means that the e option needs an argument
        switch(ch) { // The code to handle each option goes here
        // ...
        case 'e': // You’re reading the argument for the "e" option here.
            engine_count = optarg; // getopt() will point to the argument
                                   // with the optarg variable
        // ...
        }

    // These final two lines make sure we skip past the options we read
    argc -= optind;
    argv += optind;
    return 0; // optind stores the number of strings read from
              // the command line to get past the options
}
