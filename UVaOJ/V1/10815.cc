#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<string> strs;
    string s;
    while (!cin.eof())
    {
        getline(cin, s);
        auto sb = s.begin();
        auto se = s.end();
        transform(sb, se, sb, ::tolower);
        auto pred = [] (const char c) -> bool { return !isalpha(c); };
        while (sb < se) {
            auto new_sb = find_if(sb, se, pred);
            string tmp (sb, new_sb);
            if (!tmp.empty()) {
                strs.push_back(tmp);
            }
            sb = new_sb;
            ++sb;
        }
    }

    sort(strs.begin(), strs.end());

    string last;
    for (auto &str : strs)
    {
        if (str != last) {
            cout << str << endl;
            last = str;
        }
    }

    return 0;
}
