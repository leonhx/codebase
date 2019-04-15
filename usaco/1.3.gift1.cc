/*
ID: xerxes.1
PROG: gift1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
    ifstream fin ("gift1.in");
    ofstream fout ("gift1.out");

    int NP;
    fin >> NP;

    vector<string> names;
    map<string, int> money;
    for (int i = 0; i < NP; ++i) {
        string temp;
        fin >> temp;
        names.push_back(temp);
        money.insert(pair<string, int>(temp, 0));
    }

    for (int i = 0; i < NP; ++i) {
        string name;
        fin >> name;
        int total, slice;
        fin >> total >> slice;
        if (total == 0 || slice == 0) {
            string getter;
            for (int j = 0; j < slice; ++j) {
                fin >> getter;
            }
            continue;
        }
        money[name] -= total / slice * slice;
        for (int j = 0; j < slice; ++j) {
            string getter;
            fin >> getter;
            money[getter] += total / slice;
        }
    }

    for (vector<string>::const_iterator i = names.begin(); i != names.end(); ++i) {
        fout << *i << ' ' << money[*i] << endl;
    }

    return 0;
}
