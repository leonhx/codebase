#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int MAX_LEN = 100;
char name[MAX_LEN];

struct Proc
{
    char name[MAX_LEN];
    int t;
    Proc(char _name[], int _t) : t(_t) {
        strncpy(name, _name, MAX_LEN);
    }
};

queue<Proc> procs;

void schedule(const int q)
{
    int t = 0;
    while (!procs.empty())
    {
        Proc p = procs.front();
        procs.pop();
        if (p.t <= q)
        {
            t += p.t;
            printf("%s %d\n", p.name, t);
        } else {
            t += q;
            p.t -= q;
            procs.push(p);
        }
    }
}

int main()
{
    int n, q;
    scanf("%d %d\n", &n, &q);

    int t;
    for (int i = 0; i < n; i++)
    {
        scanf("%s %d\n", name, &t);
        procs.push(Proc(name, t));
    }

    schedule(q);

    return 0;
}