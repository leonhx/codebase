#include <cstdio>

char ROOM[23][23];
int DP[][2] = { { -1, 0 }, { 0, 1 }, { 0, -1 }, { 1, 0 } };
int ch;
int count;

void dfs(int x, int y)
{
    count++;
    for (int i = 0; i < 4; ++i)
    {
        int dx = DP[i][0];
        int dy = DP[i][1];
        if (ROOM[x + dx][y + dy] == '.')
        {
            ROOM[x + dx][y + dy] = '#';
            dfs(x + dx, y + dy);
        }
    }
}

int main(int argc, char const *argv[])
{
    int W, H;
    int X, Y;

    scanf("%d %d\n", &W, &H);

    while (W && H)
    {
        count = 0;

        for (int k = 0; k < W + 2; ++k)
        {
            ROOM[0][k] = ROOM[H + 1][k] = '#';
        }

        int i = 1, j = 0;
        while ((ch = getchar()) && i < H + 1)
        {
            ROOM[i][0] = '#';
            ROOM[i][W + 1] = '#';
            if (ch == '\n')
                continue;
            if (ch == '@')
            {
                X = i;
                Y = j + 1;
            }
            ROOM[i][j + 1] = ch;
            i += (j + 1) / W;
            j = (j + 1) % W;
        }

        dfs(X, Y);
        printf("%d\n", count);
        scanf("%d %d\n", &W, &H);
    }

    return 0;
}
