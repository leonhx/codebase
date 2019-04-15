#include <cstdio>

const int WIDTH = 5;
const int MAX_COMB = 1000000;
char grids[WIDTH][WIDTH];
bool bits[MAX_COMB];
char dir[][2] = {{ -1, 0}, {0, 1}, {0, -1}, {1, 0}};

char hop_seq[5] = {0, 0, 0, 0, 0};

bool next_hop_seq()
{
    int c = 1;
    for (int i = 4; i >= 0; --i)
    {
        int t = hop_seq[i] + 1;
        hop_seq[i] = t % 4;
        c = t / 4;
        if (c == 0)
            return true;
    }
    return false;
}

int count()
{
    for (int i = 0; i < WIDTH; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            do
            {
                int x = i, y = j;
                int n = grids[x][y];
                bool fail = false;
                for (int step_i = 0; step_i < 5; ++step_i)
                {
                    x += dir[hop_seq[step_i]][0];
                    y += dir[hop_seq[step_i]][1];
                    if (x < 0 || x >= WIDTH || y < 0 || y >= WIDTH)
                    {
                        fail = true;
                        break;
                    }
                    n = n * 10 + grids[x][y];
                }
                if (!fail)
                {
                    bits[n] = true;
                }
            }
            while (next_hop_seq());
        }
    }

    int c = 0;
    for (int i = 0; i < MAX_COMB; ++i)
        if (bits[i])
            c++;
    return c;
}

int main()
{
    int d;
    for (int i = 0; i < WIDTH; ++i)
        for (int j = 0; j < WIDTH; ++j)
        {
            scanf("%d", &d);
            grids[i][j] = d;
        }

    printf("%d\n", count());
    return 0;
}
