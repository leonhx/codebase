/*
 *
 * DEBUG
 *
 */

/* preprocess macro
 * usage:
 * + when debugging, include the line `#define DEBUG`,
 *   or delete it.
 * + if debug code is needed, use this way:
 *   DEBUG_CODE(
 *       statement1;
 *       statement2;
 *       statement3;
 *       ......
 *   );
 */

#define DEBUG

#if defined( DEBUG )
    #define DEBUG_CODE( code_fragment ) { code_fragment }
#else
    #define DEBUG_CODE( code_fragment )
#endif
