/*
ID: xerxes.1
PROG: palsquare
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void int2str(int n, int base, char *str) {
    int i = 0;
    while (n > 0) {
        int d = n % base;
        if (d < 10) {
            str[i] = d + '0';
        } else {
            str[i] = d - 10 + 'A';
        }
        n /= base;
        i++;
    }
    str[i] = '\0';
}

bool palindromic(char *str) {
    int len = strlen(str);
    int i = 0, j = len - 1;
    while (i < j) {
        if (str[i] != str[j])
            return false;
        i++;
        j--;
    }
    return true;
}

int main() {
    ifstream fin ("palsquare.in");
    ofstream fout ("palsquare.out");

    int base;
    fin >> base;

    char *str = new char[32];

    for (int n = 1; n <= 300; ++n) {
        int2str(n*n, base, str);
        if (palindromic(str))
            fout << n << " " << n*n << endl;
    }

    delete[] str;
    return 0;
}

