/*
ID: xerxes.1
PROG: calfflac
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <streambuf>

using namespace std;

typedef struct {
    int pos;
    int len;
    int c;
} str_t;

bool isalpha(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

char tolower(char c) {
    if ('A' <= c && c <= 'Z') {
        return c - 'A' + 'a';
    } else {
        return c;
    }
}

str_t even_palindrome(string str, int i) {
    int j = i + 1;

    while (i >= 0 && j < str.length()) {
        while (!isalpha(str[i])) {
            i--;
            if (i < 0) {
                i++;
                break;
            }
        }
        while (!isalpha(str[j])) {
            j++;
            if (j >= str.length()) {
                j--;
                break;
            }
        }
        if (tolower(str[i]) == tolower(str[j])) {
            i--;
            j++;
        } else {
            i++;
            j--;
            break;
        }
    }

    while (i < str.length() && !isalpha(str[i]))
        i++;
    while (j >= 0 && !isalpha(str[j]))
        j--;

    int c = 0;
    for (int k = i; k <= j; ++k)
    {
        if (isalpha(str[k]))
            c++;
    }

    str_t s = { i, j-i+1, c };

    return s;
}

str_t odd_palindrome(string str, int i) {
    int j = i + 1;
    i--;

    while (i >= 0 && j < str.length()) {
        while (!isalpha(str[i])) {
            i--;
            if (i < 0) {
                i++;
                break;
            }
        }
        while (!isalpha(str[j])) {
            j++;
            if (j >= str.length()) {
                j--;
                break;
            }
        }
        if (tolower(str[i]) == tolower(str[j])) {
            i--;
            j++;
        } else {
            i++;
            j--;
            break;
        }
    }

    while (i < 0 || (i < str.length() && !isalpha(str[i])))
        i++;
    while (j >= 0 && !isalpha(str[j]))
        j--;

    int c = 0;
    for (int k = i; k <= j; ++k)
    {
        if (isalpha(str[k]))
            c++;
    }

    str_t s = { i, j-i+1, c };

    return s;
}

int main() {
    ifstream fin ("calfflac.in");
    ofstream fout ("calfflac.out");

    string str;

    fin.seekg(0, std::ios::end);
    str.reserve(fin.tellg());
    fin.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(fin)),
                std::istreambuf_iterator<char>());

    int len = str.length()*2;
    str_t *P = new str_t[len];

    int max_c = 0;
    for (int i = 0; i < len; ++i)
    {
        if (i % 2 == 1)
            P[i] = odd_palindrome(str, i/2);
        else
            P[i] = even_palindrome(str, i/2);
        if (P[i].c > max_c) {
            max_c = P[i].c;
        }
    }

    fout << max_c << endl;

    int amount = 0;
    for (int i = 0; i < len; ++i)
    {
        if (P[i].c == max_c) {
            amount++;
        }
    }

    str_t *Pt = new str_t[amount];
    int k = 0;

    bool printed = false;
    for (int i = 0; i < len && !printed; ++i) {
        if (P[i].c == max_c) {
            bool flag = true;
            for (int j = 0; j < k; j++) {
                if (Pt[j].pos == P[i].pos && Pt[j].len == P[i].len) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                Pt[k++] = P[i];
                fout << str.substr(P[i].pos, P[i].len) << endl;
                printed = true;
            }
        }
    }

    delete[] Pt;
    delete[] P;
    return 0;
}
