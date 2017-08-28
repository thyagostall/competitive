#include <cstdio>

int main()
{
    int m, n, i, j, f, c, p, q;
    char field[150][150];

    f = 0;
    while (scanf("%d %d", &m, &n) && m && n) {
        for (i = 0; i < m; i++) {
            scanf(" ");
            for (j = 0; j < n; j++) {
                scanf("%c", &field[i][j]);
            }
        }
      
        if (f) printf("\n");
        printf("Field #%d:\n", ++f);
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                c = 0;
                if (field[i][j] != '*') {
                    for (p = i - 1; p <= i + 1; p++) {
                        for (q = j - 1; q <= j + 1; q++) {
                            if (p == i && q == j || p < 0 || q < 0 || p >= m || q >= n) continue;
                            if (field[p][q] == '*') c++;
                        }
                    }
                    field[i][j] = c + '0';
                }
                printf("%c", field[i][j]);
            }
            printf("\n");
        }
    }
}
