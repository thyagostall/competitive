#include <cstdio>

int main()
{
    int a, b, c, d, t, i, o, s;
    int current_player;
    int board[110];
    int players[1000005];
    bool win;

    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d", &a, &b, &c);
        
        for (i = 1; i <= 100; i++) {
            board[i] = 0;
        }
        for (i = 1; i <= a; i++) {
            players[i] = 1;
        }
        
        while (b--) {
            scanf("%d %d", &i, &o);
            board[i] = o;
        }

        win = false;
        current_player = 1;
        while (c--) {
            scanf("%d", &d);
            if (win) continue;
            
            s = players[current_player];
            if (s < 100) {
                s += d;
                s = s > 100 ? 100 : s;

                if (board[s])
                    s = board[s];
                players[current_player] = s;
            }
            win = s == 100;

            current_player++;
            if (current_player > a) current_player = 1;
        }

        for (i = 1; i <= a; i++) {
            printf("Position of player %d is %d.\n", i, players[i]);
        }
    }
}
