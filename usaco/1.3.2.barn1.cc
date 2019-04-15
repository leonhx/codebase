/*
ID: xerxes.1
PROG: barn1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

typedef struct {
    int x;
    int y;
} interval_t;

bool cmp_int(const interval_t &x, const interval_t &y) {
    return x.y - x.x > y.y - y.x;
}

int main() {
    ifstream fin ("barn1.in");
    ofstream fout ("barn1.out");

    int M, S, C;
    fin >> M >> S >> C;

    int *occupied = new int[C];
    for (int i = 0; i < C; ++i) {
        fin >> occupied[i];
    }

    sort(occupied, occupied+C);
    int sum = occupied[C-1] - occupied[0] + 1;

    interval_t *ints = new interval_t[C-1];
    for (int i = 0; i < C-1; ++i) {
        ints[i] = interval_t { occupied[i], occupied[i+1] };
    }

    sort(ints, ints+C-1, cmp_int);

    for (int i = 0; i < M-1 && i < C-1; ++i) {
        sum -= ints[i].y - ints[i].x - 1;
    }

    fout << sum << endl;

    delete[] ints;
    delete[] occupied;
    return 0;
}
