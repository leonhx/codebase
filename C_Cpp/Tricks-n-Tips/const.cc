/*
 *
 * CONST
 *
 */

/* const_iterator
 * there is no such thing like a pointer pointed to a const array
 * other than const_iterator in STL collections
 * const_iterator <-> T* const
 */

std::vector<int> vec;
// ...
const std::vector<int>::iterator iter = vec.begin();
*iter = 10; // valid
++iter; // ERROR!
std::vector<int>::const_iterator cIter = vec.begin();
*cIter = 10; // ERROR!
++cIter; // valid


/* use mutable when necessary
 * reason: sometimes you just want a const member function
 *         to modify some specified member data, but others
 *         stay unchanged
 * as the following case shows:
 */
class CTextBlock
{
public:
    // ...
    std::size_t length() const;

private:
    char* pText;
    mutable std::size_t textLength; // These member variables may
    mutable bool lenghtIsValid;     // be changed even in const
};                                  // memeber functions.

std::size_t length() const
{
    if (!lenghtIsValid) {                // It is necessary to do
        textLength = std::strlen(pText); // like this and at the same
        lenghtIsValid = true;            // time ensure other member
    }                                    // variables unchanged
    return textLength;
}


/* Avoiding Duplication in const and Non-const Member Functions
 */
// code duplication, along with its attendant compilation time,
// maintenance, and code-bloat headaches:
class TextBlock {
public:
    // ...

    const char& operator[](std::size_t position) const
    {
        // do bounds checking
        // log access data
        // verify data integrity
        return text[position];
    }

    char& operator[](std::size_t position)
    {
        // do bounds checking
        // log access data
        // verify data integrity
        return text[position];
    }

private:
    std::string text;
};

// there is a better but not elegant way:
class TextBlock {
public:
    // ...

    const char& operator[](std::size_t position) const
    {
        // same as before
        return text[position];
    }

    char& operator[](std::size_t position)
    { // now just calls const op[]
        return
            const_cast<char&>( // cast away const on op[]'s return type;
                static_cast<const TextBlock&>(*this) // add const to
                                                     // *this's type;
                    [position] // call const version of op[]
            );
    }
    // ...
};
