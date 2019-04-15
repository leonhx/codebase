#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_H = 102;
const int MAX_W = 102;

int H, W, Sx, Sy;

int solve(int x, int y, char board[MAX_H][MAX_W], int n_steps) {
    if (n_steps >= 10)
        return -1;

    char four_directions[4];
    int N = 0;

    if (x > 0 && board[x-1][y] != 1) {
        for (int i = x; i >= 0; --i)
        {
            char c = board[i][y];
            if (c == 3)
                return 1 + n_steps;
            if (c == 1) {
                board[i][y] = 0;
                four_directions[N++] = solve(i+1, y, board, n_steps+1);
                board[i][y] = 1;
                break;
            }
        }
    }

    if (x < H-1 && board[x+1][y] != 1) {
        for (int i = x; i < H; ++i)
        {
            char c = board[i][y];
            if (c == 3)
                return 1 + n_steps;
            if (c == 1) {
                board[i][y] = 0;
                four_directions[N++] = solve(i-1, y, board, n_steps+1);
                board[i][y] = 1;
                break;
            }
        }
    }

    if (y > 0 && board[x][y-1] != 1) {
        for (int i = y; i >= 0; --i)
        {
            char c = board[x][i];
            if (c == 3)
                return 1 + n_steps;
            if (c == 1) {
                board[x][i] = 0;
                four_directions[N++] = solve(x, i+1, board, n_steps+1);
                board[x][i] = 1;
                break;
            }
        }
    }

    if (y < W-1 && board[x][y+1] != 1) {
        for (int i = y; i < W; ++i)
        {
            char c = board[x][i];
            if (c == 3)
                return 1 + n_steps;
            if (c == 1) {
                board[x][i] = 0;
                four_directions[N++] = solve(x, i-1, board, n_steps+1);
                board[x][i] = 1;
                break;
            }
        }
    }

    int min_steps = 11;
    for (int i = 0; i < N; ++i)
    {
        if (four_directions[i] != -1 && four_directions[i] < min_steps)
            min_steps = four_directions[i];
    }

    if (min_steps > 10)
        return -1;
    else
        return min_steps;
}

int main(int argc, char const *argv[])
{
    char board[MAX_H][MAX_W];
    scanf("%d %d\n", &W, &H);
    while (H && W) {
        for (int i = 0; i < H; ++i)
        {
            for (int j = 0; j < W; ++j)
            {
                scanf("%d", &board[i][j]);
                if (board[i][j] == 2) {
                    Sx = i;
                    Sy = j;
                    board[i][j] = 0;
                }
            }
        }

        printf("%d\n", solve(Sx, Sy, board, 0));
        scanf("%d %d\n", &W, &H);
    }

    return 0;
}
