#include <cstdio>

#define MARK -1

int card[5][5];

void mark_number(int n)
{
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (card[i][j] == n) {
                card[i][j] = MARK;
            }
        }
    }
}

bool check_bingo()
{
    int i;
    for (i = 0; i < 5; i++) {
        if (card[i][0] == MARK &&
            card[i][1] == MARK &&
            card[i][2] == MARK &&
            card[i][3] == MARK &&
            card[i][4] == MARK)
            return true;
    }
    
    for (i = 0; i < 5; i++) {
        if (card[0][i] == MARK &&
            card[1][i] == MARK &&
            card[2][i] == MARK &&
            card[3][i] == MARK &&
            card[4][i] == MARK)
            return true;
    }

    if (card[0][0] == MARK &&
        card[1][1] == MARK &&
        card[2][2] == MARK &&
        card[3][3] == MARK &&
        card[4][4] == MARK)
        return true;
    
    if (card[0][4] == MARK &&
        card[1][3] == MARK &&
        card[2][2] == MARK &&
        card[3][1] == MARK &&
        card[4][0] == MARK)
        return true;

    return false;
}

int main()
{
    int t, n, c, i, j;
    
    scanf("%d", &t);
    while (t--) {
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                if (i == 2 && j == 2)
                    card[i][j] = MARK;
                else
                    scanf("%d", &card[i][j]);
            }
        }

        n = 1;
        for (i = 0; i < 75; i++) {
            scanf("%d", &c);
            mark_number(c);
            if (!check_bingo()) n++;
        }

        printf("BINGO after %d numbers announced\n", n);
    }
}
