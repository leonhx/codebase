/*
ID: xerxes.1
PROG: ride
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    const string go("GO");
    const string stay("STAY");

    ofstream fout ("ride.out");
    ifstream fin ("ride.in");
    string a, b;
    fin >> a >> b;

    int an = 1, bn = 1;
    for (string::iterator it = a.begin(); it != a.end(); it++) {
        an *= (*it) - 'A' + 1;
        an %= 47;
    }
    for (string::iterator it = b.begin(); it != b.end(); it++) {
        bn *= (*it) - 'A' + 1;
        bn %= 47;
    }

    if (an == bn) {
        fout << go << endl;
    } else {
        fout << stay << endl;
    }

    return 0;
}

