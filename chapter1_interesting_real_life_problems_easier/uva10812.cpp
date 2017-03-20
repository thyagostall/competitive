#include <cstdio>

#define ll long long

int main()
{
    int n;
    ll a, b, x, y;
    scanf("%d", &n);
    while (n--) {
        scanf("%lld %lld", &a, &b);
        
        x = (a - b) / 2;
        y = (a - b) / 2 + b;

        if (a < b || x + y != a) {
            printf("impossible\n");
        } else {
            printf("%lld %lld\n", y, x);
        }
    }
}
