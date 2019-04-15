#include <cstdio>
#include <stack>
#include <vector>

using namespace std;

stack<int> stk;
vector<int> areas;

int main()
{
    int ch;
    int sum = 0;
    int current_point = 0;
    int area = 0;
    int last_s = 0, last_e = 0;
    while ((ch = getchar()) && ch != '\n' && ch != EOF)
    {
        switch (ch)
        {
            case '\\':
                stk.push(current_point);
                break;
            case '/':
                if (!stk.empty())
                {
                    int p = stk.top();
                    stk.pop();
                    area += current_point - p;
                    if (p >= last_s || last_e >= current_point) {
                        sum += area;
                        areas.push_back(area);
                        area = 0;
                    }
                    last_s = p;
                    last_e = current_point;
                }
                break;
        }
        current_point++;
    }

    printf("%d\n", sum);
    printf("%d", areas.size());
    for (int i = 0; i < areas.size(); ++i)
        printf(" %d", areas[i]);
    putchar('\n');
    return 0;
}
