#include <cstdio>

int G[101];
int A[1000002];

int insertion_sort(int *A, int n, int g)
{
    int cnt = 0;
    for (int i = g; i < n; ++i)
    {
        int v = A[i];
        int j = i - g;
        while (j >= 0 && A[j] > v)
        {
            A[j+g] = A[j];
            j -= g;
            cnt++;
        }
        A[j+g] = v;
    }
    return cnt;
}

int shell_sort(int *A, int n)
{
    int cnt = 0;
    G[0] = 1;
    int m = 0;
    do {
        G[m+1] = G[m] * 3 + 1;
    } while (G[++m] < n);
    printf("%d\n", m);
    for (int i = m-1; i >= 0; --i) {
        if (i < m-1) putchar(' ');
        printf("%d", G[i]);
        cnt += insertion_sort(A, n, G[i]);
    }
    printf("\n%d\n", cnt);
    for (int i = 0; i < n; ++i)
        printf("%d\n", A[i]);
}

int main(int argc, char const *argv[])
{
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        scanf("%d", &A[i]);

    shell_sort(A, N);

    return 0;
}
