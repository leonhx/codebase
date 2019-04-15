#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Point
{
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}
};

struct PointT
{
    Point p;
    int t;
    PointT() : p(), t(0) {}
    PointT(Point _p, int _t) : p(_p), t(_t) {}
};

int lattice[320][320];
queue<Point> ps;
char dir[][2] = {{ -1, 0}, {0, 1}, {0, -1}, {1, 0}};

void bfs()
{
    int size = ps.size();
    while (size-- > 0)
    {
        Point p = ps.front();
        ps.pop();
        int t = lattice[p.x][p.y];
        if (t < 0)
            continue;
        for (int i = 0; i < 4; ++i)
        {
            int nx = p.x + dir[i][0], ny = p.y + dir[i][1];
            if (nx < 0 || nx >= 320 || ny < 0 || ny >= 320)
                continue;
            if (lattice[nx][ny] == -1)
            {
                lattice[nx][ny] = t + 1;
                ps.push(Point(nx, ny));
            }
        }
    }
}

bool cmp(PointT pt1, PointT pt2) { return pt1.t < pt2.t; }

int main(int argc, char const *argv[])
{
    memset(lattice, -1, sizeof(lattice));
    ps.push(Point(0, 0));
    lattice[0][0] = 0;

    int M;
    scanf("%d\n", &M);
    vector<PointT> pts;
    for (int i = 0; i < M; ++i)
    {
        int x, y, t;
        scanf("%d %d %d\n", &x, &y, &t);
        pts.push_back(PointT(Point(x, y), t));
    }
    sort(pts.begin(), pts.end(), cmp);

    int last_t = 0;
    int t;
    for (int i = 0; i < M; ++i)
    {
        if (ps.empty())
            break;
        Point p = pts[i].p;
        int t = pts[i].t;
        for (int j = last_t; j < t; ++j)
            bfs();
        lattice[p.x][p.y] = -2;
        for (int i = 0; i < 4; ++i)
        {
            int nx = p.x + dir[i][0], ny = p.y + dir[i][1];
            if (nx < 0 || nx >= 320 || ny < 0 || ny >= 320)
                continue;
            lattice[nx][ny] = -2;
        }

        last_t = t;
    }

    int min_t = 2000;
    for (int i = 0; i < 320; ++i)
        for (int j = 0; j < 320; ++j)
            if (lattice[i][j] >= 0 && lattice[i][j] < min_t)
                min_t = lattice[i][j];

    if (min_t > 1000)
        min_t = -1;

    printf("%d\n", min_t);

    return 0;
}
