#include <cstdio>

using namespace std;

int max(int a, int b) 
{
    return a > b ? a : b;
}

int main()
{
    int T, N, C, i, speed;
    scanf("%d", &T);
    for (i = 1; i <= T; i++) {
        speed = 0;

        scanf("%d", &N);
        while (N--) {
            scanf("%d", &C);
            speed = max(speed, C);
        }

        printf("Case %d: %d\n", i, speed);
    } 
}
