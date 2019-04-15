#include <cstdio>
#include <algorithm>

using namespace std;

const int INF = 1000000000;
const int MAX_N = 12;
char digits[MAX_N];
int N;

char next_digit()
{
    int ch;
    while ((ch = getchar()) && ch == ' ')
        ;
    if (ch == '\n') return -1;
    else return ch - '0';
}

int min_diff()
{
    sort(digits, digits + N);
    if (N == 2) return digits[1] - digits[0];

    int t = INF, m = INF;
    for (int i = 0; i < N - 1; ++i)
    {
        if (digits[i] != 0)
        {
            t = digits[i + 1] - digits[i];
            if (t < m)
                m = t;
        }
    }

    const int n = N / 2;

    if ((N & 1) == 1)
    {
        int a = 0, b = 0;
        for (int i = 0; i < n; ++i)
            b = b * 10 + digits[--N];

        int i = 0;
        if (digits[0] == 0)
        {
            if (N > 1)
                a = digits[1] * 10;
            else a = 0;
            i = 2;
        }
        while (i < N)
            a = a * 10 + digits[i++];

        return a - b;
    }

    int diff = INF, ta, tb;
    for (int i = 0; i < N - 1; ++i)
    {
        ta = digits[i + 1];
        tb = digits[i];
        if (digits[i] != 0 && ta - tb == m)
        {
            int c = 1;
            for (int j = 0; j < N; ++j)
            {
                if (j != i && j != i + 1)
                {
                    if (c >= n) break;
                    ta = ta * 10 + digits[j];
                    c++;
                }
            }
            c = 1;
            for (int j = N-1; j >= 0; --j)
            {
                if (j != i && j != i + 1)
                {
                    if (c >= n) break;
                    tb = tb * 10 + digits[j];
                    c++;
                }
            }
            if (ta - tb < diff)
                diff = ta - tb;
        }
    }

    return diff;
}

int main()
{
    int n;
    scanf("%d\n", &n);
    int d = 0;
    while (n-- > 0)
    {
        N = 0;
        while ((d = next_digit()) != -1)
            digits[N++] = d;
        printf("%d\n", min_diff());
    }

    return 0;
}
