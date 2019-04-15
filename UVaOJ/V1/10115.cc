#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

bool replace(string &str, const string &from, const string &to)
{
    size_t start_pos = str.find(from);
    if (start_pos == string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void apply_rules(string &str, vector<string> rules)
{
    for (auto i = rules.begin(); i != rules.end(); i += 2)
    {
        string from = *i;
        string to = *(i + 1);
        while (replace(str, from, to))
            ;
    }
}

int main(int argc, char const *argv[])
{
    string tmp;
    int i = 0;
    while (!cin.eof())
    {
        getline(cin, tmp);
        int N = atoi(tmp.c_str());
        if (N == 0)
            break;
        vector<string> rules;
        while (N-- > 0)
        {
            getline(cin, tmp);
            rules.push_back(tmp);
            getline(cin, tmp);
            rules.push_back(tmp);
        }
        getline(cin, tmp);
        apply_rules(tmp, rules);
        cout << tmp << endl;
        i++;
    }

    return 0;
}
