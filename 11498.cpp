#include <cstdio>

void print_location(int x, int y, int n, int m) {
    if (x == n || y == m) {
        printf("divisa\n");
        return;
    }

    if (y > m) {
        printf("N");
    } else {
        printf("S");
    }

    if (x > n) {
        printf("E");
    } else {
        printf("O");
    }
    printf("\n");
}

int main()
{
    int k, n, m, x, y;

    while (scanf("%d", &k) && k != 0) {
        scanf("%d %d", &n, &m);
        while (k--) {
            scanf("%d %d", &x, &y);
            print_location(x, y, n, m);
        }
    }
}
