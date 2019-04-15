#include <cstdio>
#include <stack>
#include <queue>

using namespace std;

struct Area {
    int s;
    int e;
    int area;
    Area(int _s, int _e) : s(_s), e(_e), area(_e - _s) {}
};

stack<int> stk;
queue<Area> areas;

int main()
{
    int ch;
    int sum = 0;
    int current_point = 0;
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
                    Area area(p, current_point);
                    sum += area.area;
                    int size = areas.size();
                    while (size-- > 0)
                    {
                        Area a = areas.front();
                        areas.pop();
                        if (area.s < a.s && a.e < area.e)
                            area.area += a.area;
                        else
                            areas.push(a);
                    }
                    areas.push(area);
                }
                break;
        }
        current_point++;
    }

    printf("%d\n", sum);
    printf("%d", areas.size());
    while (!areas.empty())
    {
        Area a = areas.front();
        areas.pop();
        printf(" %d", a.area);
    }
    putchar('\n');
    return 0;
}
