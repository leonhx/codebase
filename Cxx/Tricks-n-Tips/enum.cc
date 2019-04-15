/*
 *
 * ENUM
 *
 */

/* enum hack
 * reason: compiler may not allow static (integer) member in a
 *         class be initialized, and you might need the member
 *         when an object of the class being initialized
 * other reasons:
 * + enum hack behaves more like `#define` rather than `const`
 * + enum hack and `#define` will never lead to unnecessary memory
 *   allocation
 * + basic technique of template metaprogramming
 */

class GamePlayer
{
private:
    enum { NumTurns = 5 };

    int score[NumTurns];
    // ...
};
