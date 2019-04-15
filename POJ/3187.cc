#include <cstdio>

int nums[12];

int C(int n, int i)
{
    if (n - i < i)
        i = n - i;
    int result = 1;
    for (int j = 0; j < i; ++j)
    {
        result *= (n - j);
        result /= (j + 1);
    }
    return result;
}

void init(int N)
{
    for (int i = 0; i < N; ++i)
        nums[i] = i;
}

bool has_before(int i, int n)
{
    while (i > 0)
    {
        if (nums[--i] == n)
            return true;
    }
    return false;
}

bool next_perm(int N)
{
    int c = 1;
    for (int i = N - 1; i >= 0; --i)
    {
        do
        {
            int t = nums[i] + 1;
            nums[i] = t % N;
            c = t / N;
        }
        while (c == 0 && has_before(i, nums[i]));
        if (c == 0)
        {
            for (int j = i + 1; j < N; ++j)
            {
                for (int k = 0; k < N; ++k)
                {
                    if (!has_before(j, k))
                    {
                        nums[j] = k;
                        break;
                    }
                }
            }
            return true;
        }
    }
    return false;
}

int iterative_sum(int N)
{
    int sum = 0;
    for (int i = 0; i < N; ++i)
        sum += C(N - 1, i) * (nums[i] + 1);
    return sum;
}

void backward(int sum, int N)
{
    init(N);
    do
    {
        if (iterative_sum(N) == sum)
            return;
    }
    while (next_perm(N));
}

int main()
{
    int N, sum;
    scanf("%d %d", &N, &sum);

    backward(sum, N);
    for (int i = 0; i < N; ++i)
    {
        if (i > 0) putchar(' ');
        printf("%d", nums[i] + 1);
    }
    putchar('\n');
    return 0;
}
