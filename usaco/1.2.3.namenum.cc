/*
ID: xerxes.1
PROG: namenum
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

const string NONE("NONE");
const string KEYPAD("ABCDEFGHIJKLMNOPRSTUVWXY");

typedef long long int uint64;

uint64 str2key(string s) {
    uint64 i = 0;
    for (char& c : s) {
        i *= 10;
        size_t found = KEYPAD.find(c);
        if (found != string::npos) {
            i += found / 3 + 2;
        } else {
            return 0;
        }
    }

    return i;
}

int main() {
    ifstream fin ("namenum.in");
    ifstream fdict ("dict.txt");
    ofstream fout ("namenum.out");

    map<uint64, vector<string>> dict;
    string t;
    while (!fdict.eof()) {
        fdict >> t;
        uint64 key = str2key(t);
        if (key != 0) {
            dict[key].push_back(t);
        }
    }

    uint64 key;
    fin >> key;

    auto it = dict.find(key);
    if (it == dict.end()) {
        fout << NONE << endl;
    } else {
        auto values = it->second;
        for (auto i = values.begin(); i != values.end(); ++i) {
            fout << *i << endl;
        }
    }

    return 0;
}

