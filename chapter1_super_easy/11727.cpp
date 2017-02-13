#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    int t, s[3];

    scanf("%d", &t);
    for (int c = 1; c <= t; c++) {
        scanf("%d %d %d", &s[0], &s[1], &s[2]);
        sort(s, s + 3);
        printf("Case %d: %d\n", c, s[1]);
    }
}
