/*
ID: xerxes.1
PROG: transform
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

bool fit1(string *x, string *y, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (x[i][j] != y[j][N-i-1])
                return false;
        }
    }
    return true;
}

bool fit2(string *x, string *y, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (x[i][j] != y[N-i-1][N-j-1])
                return false;
        }
    }
    return true;
}

bool fit3(string *x, string *y, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (x[i][j] != y[N-j-1][i])
                return false;
        }
    }
    return true;
}

bool fit4(string *x, string *y, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (x[i][j] != y[i][N-j-1])
                return false;
        }
    }
    return true;
}

bool fit5(string *x, string *y, int N) {
    string *new_x = new string[N];
    for (int i = 0; i < N; ++i) {
        new_x[i] = x[i];
        for (int j = 0; j < N; ++j) {
            new_x[i][j] = x[i][N-j-1];
        }
    }

    assert(fit4(x, new_x, N));

    bool then = fit1(new_x, y, N) || fit2(new_x, y, N) || fit3(new_x, y, N);
    delete[] new_x;
    return then;
}

bool fit6(string *x, string *y, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (x[i][j] != y[i][j])
                return false;
        }
    }
    return true;
}

int main() {
    ifstream fin ("transform.in");
    ofstream fout ("transform.out");

    int N;
    fin >> N;

    string *tiles_x = new string[N];
    for (int i = 0; i < N; ++i) {
        fin >> tiles_x[i];
    }

    string *tiles_y = new string[N];
    for (int i = 0; i < N; ++i) {
        fin >> tiles_y[i];
    }

    if (fit1(tiles_x, tiles_y, N))
        fout << 1 << endl;
    else if (fit2(tiles_x, tiles_y, N))
        fout << 2 << endl;
    else if (fit3(tiles_x, tiles_y, N))
        fout << 3 << endl;
    else if (fit4(tiles_x, tiles_y, N))
        fout << 4 << endl;
    else if (fit5(tiles_x, tiles_y, N))
        fout << 5 << endl;
    else if (fit6(tiles_x, tiles_y, N))
        fout << 6 << endl;
    else
        fout << 7 << endl;

    delete[] tiles_x;
    delete[] tiles_y;
    return 0;
}

