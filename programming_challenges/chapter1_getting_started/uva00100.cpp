#include <cstdio>

int cycle_length(int number)
{
    int result = 1;
    while (number != 1) {
        if (number % 2) {
            number = 3 * number + 1;
        } else {
            number = number / 2;
        }
        result++;
    }
    return result;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int max_cycle(int i, int j)
{
    int result = 0;
    for (int x = i; x <= j; x++) {
        result = max(result, cycle_length(x));
    }
    return result;
}

int main()
{
    int result, i, j;
    while (scanf("%d %d", &i, &j) != EOF) {
        if (j > i) {
            result = max_cycle(i, j);
        } else {
            result = max_cycle(j, i);
        }
        printf("%d %d %d\n", i, j, result);
    }
}
