/*
ID: xerxes.1
PROG: dualpal
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void int2str(int n, int base, char* str) {
    int i = 0;
    while (n > 0) {
        int x = n % base;
        str[i++] = x + '0';
        n /= base;
    }
    str[i] = '\0';
}

bool pal(char* str) {
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
    ifstream fin ("dualpal.in");
    ofstream fout ("dualpal.out");

    int N, S;
    fin >> N >> S;

    char* str = new char[20];

    int i = 0;
    while (i < N) {
        int npal = 0;
        S++;
        for (int base = 2; base <= 10; ++base){
            int2str(S, base, str);
            if (pal(str)) {
                npal++;
                if (2 <= npal) {
                    fout << S << endl;
                    i++;
                    break;
                }
            }
        }
    }

    delete[] str;
    return 0;
}

