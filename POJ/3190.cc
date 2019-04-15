#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

const int MAX_N = 50000;

struct Cow
{
    int i;
    int x;
    int y;
    int stall;
    Cow(): i(0), x(0), y(0), stall(0) {}
    bool operator< (const Cow &that) const
    {
        return x < that.x || (x == that.x && y < that.y);
    }
};

struct Stall
{
    int i;
    int endtime;
    Stall(): i(0), endtime(0) {}
    Stall(int _i, int _et): i(_i), endtime(_et) {}
    bool operator< (const Stall &that) const
    {
        return endtime > that.endtime;
    }
};

bool cmpByI(const Cow &a, const Cow &b)
{
    return a.i < b.i;
}

Cow cows[MAX_N];
priority_queue<Stall> stalls;
int N;

void assign()
{
    sort(cows, cows + N);
    for (int i = 0; i < N; ++i)
    {
        if (stalls.empty() || stalls.top().endtime >= cows[i].x) {
            Stall s(stalls.size(), cows[i].y);
            cows[i].stall = s.i;
            stalls.push(s);
        } else {
            Stall t = stalls.top();
            stalls.pop();
            t.endtime = cows[i].y;
            cows[i].stall = t.i;
            stalls.push(t);
        }
    }
}

int main()
{
    scanf("%d\n", &N);
    for (int i = 0; i < N; ++i)
    {
        scanf("%d %d\n", &cows[i].x, &cows[i].y);
        cows[i].i = i;
    }

    assign();
    printf("%lu\n", stalls.size());
    sort(cows, cows + N, cmpByI);
    for (int i = 0; i < N; ++i)
        printf("%d\n", cows[i].stall + 1);

    return 0;
}
