#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

bool immediately_decodable(vector<string> strs) {
    sort(strs.begin(), strs.end());

    for (auto iter = strs.begin(); iter != strs.end() - 1; ++iter) {
        string a = *iter;
        string b = *(iter + 1);
        bool is_diff = false;
        for (int i = 0; i < min(a.size(), b.size()); ++i) {
            if (a[i] != b[i]) {
                is_diff = true;
                break;
            }
        }
        if (!is_diff) {
            return false;
        }
    }

    return true;
}

int main(int argc, char const *argv[])
{
    int i = 0;
    while (!cin.eof()) {
        ++i;
        vector<string> strs;
        string s;
        while (!cin.eof()) {
            cin >> s;
            if (s.empty() || s[0] == '9')
                break;
            strs.push_back(s);
        }
        if (strs.empty())
            break;
        cout << "Set " << i << " is ";
        if (!immediately_decodable(strs)) {
            cout << "not ";
        }
        cout << "immediately decodable" << endl;
    }

    return 0;
}
