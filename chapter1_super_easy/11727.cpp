#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int t;
    vector<int> s(3, 0);

    scanf("%d", &t);
    for (int c = 1; c <= t; c++) {
        scanf("%d %d %d", &s[0], &s[1], &s[2]);
        sort(begin(s), end(s));
        printf("Case %d: %d\n", c, s[1]);
    }
}
