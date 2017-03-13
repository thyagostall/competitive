#include <cstdio>

char civ[101][101];
char end_day[101][101];

void empty()
{
    int i, j;
    for (i = 0; i < 100; i++)
        for (j = 0; j < 100; j++)
            civ[i][j] = end_day[i][j] = ' ';
}

void empty_end_day(int r, int c)
{
    int i, j;
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            end_day[i][j] = ' ';
}

void copy(int r, int c)
{
    int i, j;
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            if (end_day[i][j] != ' ') civ[i][j] = end_day[i][j];
}

void mark(int i, int j, char c)
{
    if (i < 0 || j < 0)
        return;

    char win;
    if (c == 'P')
        win = 'R';
    else if (c == 'R')
        win = 'S';
    else 
        win = 'P';

    if (civ[i][j] == win)
        end_day[i][j] = c;
}

void check(int i, int j)
{
    mark(i - 1, j, civ[i][j]);
    mark(i + 1, j, civ[i][j]);
    mark(i, j - 1, civ[i][j]);
    mark(i, j + 1, civ[i][j]);
}

int main()
{
    int t, r, c, n, i, j;

    scanf("%d", &t);
    empty();
    while (t--) {
        scanf("%d %d %d", &r, &c, &n);
        for (i = 0; i < r; i++) {
            scanf("%s", civ[i]);
        }

        while (n--) {
            empty_end_day(r, c);
            for (i = 0; i < r; i++)
                for (j = 0; j < c; j++)
                    check(i, j);

            copy(r, c);
        }
        for (i = 0; i < r; i++) {
            printf("%s\n", civ[i]);
        }
        if (t) printf("\n");
    }
}
