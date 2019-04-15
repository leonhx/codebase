/*
ID: xerxes.1
PROG: beads
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;

//  w b b w r b w w w b r b b b w r r r
//                      ^ ^
//                   left i/right

int count(char *beads, int len, int i) {
    int left = (i-1+len)%len;
    int right = i;

    char cl, cr, t;
    while ((cl = beads[left]) == 'w' && left != right)
        left = (left-1+len)%len;
    while ((cr = beads[right]) == 'w' && right != left)
        right = (right+1)%len;

    while (((t = beads[left]) == cl || t == 'w') && left != right)
        left = (left-1+len)%len;
    while (((t = beads[right]) == cr || t == 'w') && right != left)
        right = (right+1)%len;

    if (left < right)
        return right - left - 1;
    else if (left > right)
        return len - (left - right + 1);
    else
        return len;
}

int main() {
    ifstream fin ("beads.in");
    ofstream fout ("beads.out");

    int len;
    fin >> len;

    char *beads = new char[len];
    for (int i = 0; i < len; ++i) {
        fin >> beads[i];
    }

    bool flag = false;
    char c_flag, t;
    int max_count = count(beads, len, 0);
    for (int i = 0; i < len; ++i) {
        if ((t = beads[i]) != 'w') {
            if (!flag) {
                flag = true;
                c_flag = t;
            } else if (t != c_flag) {
                flag = false;
                int c = count(beads, len, i);
                if (c > max_count)
                    max_count = c;
            }
        }
    }

    fout << max_count << endl;

    delete[] beads;
    return 0;
}

