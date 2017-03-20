#include <cstdio>

float min(float a, float b)
{
    return a < b ? a : b;
}

float abs(float x)
{
    return x < 0 ? x * -1 : x;
}

int main()
{
    int h, m;
    float a1, a2, r;

    while (scanf("%d:%d", &h, &m) && (h || m)) {
        a1 = 30 * h + 0.5 * m;
        a2 = 6 * m;

        r = abs(a1 - a2);
        r = min(r, 360 - r);

        printf("%.3f\n", r);
    }
}
