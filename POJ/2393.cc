#include <cstdio>

const int INF = 10000;

int N, S;

inline int min(int x, int y) {
    return x < y ? x : y;
}

int main()
{
    scanf("%d %d\n", &N, &S);

    int lowest_cost_per_unit = INF;
    long long int total_cost = 0;
    for (int i = 0; i < N; ++i)
    {
        int C, Y;
        scanf("%d %d\n", &C, &Y);
        lowest_cost_per_unit = min(lowest_cost_per_unit + S, C);
        total_cost += lowest_cost_per_unit * Y;
    }

    printf("%lld\n", total_cost);
    return 0;
}
