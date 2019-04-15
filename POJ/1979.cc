#include <cstdio>

char ROOM[21][21];
int DP[][2] = { { -1, 0 }, { 0, 1 }, { 0, -1 }, { 1, 0 } };
int X, Y;
int ch;

int next_char() {
    while (ch = getchar() && ch == '\n')
        ;
    return ch;
}

int main(int argc, char const *argv[])
{
    int W, H;
    scanf("%d %d\n", &W, &H);

    while (W != 0 && H != 0) {
        int i = 0, j = 0;
        while (ch = next_char()) {
            ROOM[i][j] = ch;
            i += (j + 1) / W;
            j += (j + 1) % W;
        }

        scanf("%d %d\n", &W, &H);
    }

    return 0;
}
