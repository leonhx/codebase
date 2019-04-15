#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAX_N = 1000;

struct Point
{
    double x;
    double y;
    Point(): x(0), y(0) {}
    Point(double _x, double _y): x(_x), y(_y) {}
};

Point islands[MAX_N];
int n;
double d;

bool cmp_by_x(const Point &p1, const Point &p2)
{
    return p1.x < p2.x;
}

inline int square(double x)
{
    return x * x;
}

inline bool island_in_radar(int i, double radar)
{
    Point island = islands[i];
    return square(island.x - radar) + square(island.y) <= square(d);
}

inline int covers(int i, double radar)
{
    int c = 0;
    while (i < n && islands[i].x <= radar && radar <= islands[i].y)
    {
        c++;
        i++;
    }
    return c;
}

inline double install_radar(int i)
{
    int j = 0;
    Point island = islands[i];
    double radar = island.x;
    double best_radar = radar;
    int best_covers = covers(i, radar);
    while (islands[i+j/2].x <= island.y)
    {
        int c = covers(i, radar);
        if (c > best_covers) {
            best_radar = radar;
            best_covers = c;
        }
        j++;
        if (j % 2 == 1)
            radar = islands[i + j/2].y;
        else radar = islands[i + j/2].x;
    }
    return best_radar;
}

int min_num_radars()
{
    if (d <= 0) return -1;

    for (int i = 0; i < n; ++i)
    {
        double x = islands[i].x, y = islands[i].y;
        if (d < y) return -1;
        double r = sqrt(square(d) - square(y));
        islands[i].x = x - r;
        islands[i].y = x + r;
    }

    sort(islands, islands + n, cmp_by_x);

    double last_radar = islands[0].x - 1;
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        if (islands[i].x <= last_radar && last_radar <= islands[i].y)
            continue;
        last_radar = install_radar(i);
        count++;
    }

    return count;
}

int main()
{
    for (int i = 1; true; ++i)
    {
        scanf("%d %lf\n", &n, &d);
        if (n == 0 && d == 0)
            break;
        for (int j = 0; j < n; ++j)
            scanf("%lf %lf\n", &islands[j].x, &islands[j].y);
        printf("Case %d: %d\n", i, min_num_radars());
    }

    return 0;
}
