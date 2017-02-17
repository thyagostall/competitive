#include <cstdio>

using namespace std;

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    int H, U, D, F, d;
    float h, u, f;
    
    while (scanf("%d %d %d %d", &H, &U, &D, &F) != EOF && H) {
        d = 0, h = 0, u = U;
        f = U * F / 100.;
        
        do {
            d++;
            u = max(u - f, 0);
            h += u;

            if (h > H) 
                break;
            h -= D;
        } while (h >= 0);    

        if (h > H) {
            printf("success on day %d\n", d);
        } else {
            printf("failure on day %d\n", d);
        }
    }
}
