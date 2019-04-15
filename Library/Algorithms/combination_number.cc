// Combination number: C(n, i) = n!/((n-i)! * i!)
int combination_number(int n, int i)
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
