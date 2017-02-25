#include <cstdio>
#include <unordered_set>

using namespace std;

int get_next_card(int card, unordered_set<int> &set)
{
    while (++card && set.find(card) != set.end());
    return card <= 52 ? card : -1;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    int C, P1[3], P2[3], i, j, c, p1, p2, w, cand, f;
    unordered_set<int> set;

    while (true) {
        set.clear();
        P2[2] = 0;
        
        for (i = 0; i < 3; i++) {
            scanf("%d", &P1[i]);
            set.insert(P1[i]);
        }
        for (i = 0; i < 2; i++) {
            scanf("%d", &P2[i]);
            set.insert(P2[i]);
        }
        if (!P1[0]) 
            break;
  
        f = -1;
        for (i = 0; i < 3; i++) {
            w = 0;
            for (j = 0; j < 3; j++) {
                c = (i + j) % 3;

                p1 = P1[j];
                p2 = P2[c];

                if (p2 > p1) {
                    w++;
                }
                
                if (p2 == 0) {
                    cand = get_next_card(p1, set);
                }
//                printf("%2d - %2d | ", p1, p2);
            }

            if (w == 2) {
                cand = 0;
//                printf("cand = %2d; ", cand);
//                printf("WON\n");
            } else if (w == 1) {
//                printf("cand = %2d; ", cand);
//                printf("ONE MORE\n");
            } else {
                f = cand = -1;
//                printf("cand = %2d; ", cand);
//                printf("LOST\n");
                break;
            }

            f = max(f, cand);
        }
        if (f == 0) {
            f = get_next_card(0, set);
        }
        printf("%d\n", f);
    }
}
