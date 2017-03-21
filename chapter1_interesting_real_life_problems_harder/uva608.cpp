#include <cstdio>
#include <cstring>

int main()
{
    int t, i;
    char coins_left[10], coins_right[10], result[5];
    
    scanf("%d", &t);
    while (t--) {
        for (i = 0; i < 3; i++) {
            scanf("%s %s %s", coins_left, coins_right, result);
            printf("%s %s %s\n", coins_left, coins_right, result);
        }
    }
}
