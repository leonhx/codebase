#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 25000;

struct Interval
{
    int start;
    int end;
    Interval(): start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

Interval intervals[MAX_N];
int N, T;

bool cmp(const Interval &i1, const Interval &i2)
{
    return (i1.start < i2.start);
}

Interval *largest_end_interval(Interval **piter, Interval *end, int last_end)
{
    Interval *largest = *piter;
    bool valid_init = false;
    while ((*piter) != end && (*piter)->start <= last_end + 1)
    {
        valid_init = true;
        if ((*piter)->end > largest->end)
            largest = *piter;
        (*piter)++;
    }
    if (valid_init) return largest;
    else return 0;
}

int search()
{
    sort(intervals, intervals + N, cmp);

    int latest_end = 0, count = 0;

    Interval *iter = intervals;
    Interval *end = intervals + N;
    while (iter != end && latest_end < T)
    {
        Interval *largest = largest_end_interval(&iter, end, latest_end);
        if (largest == 0)
            break;
        latest_end = largest->end;
        count++;
    }

    if (latest_end < T)
        count = -1;

    return count;
}

int main()
{
    scanf("%d %d\n", &N, &T);
    for (int i = 0; i < N; ++i)
        scanf("%d %d\n", &intervals[i].start, &intervals[i].end);

    printf("%d\n", search());
    return 0;
}
