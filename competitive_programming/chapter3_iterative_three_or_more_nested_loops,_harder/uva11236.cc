#include <cstdio>
#include <cmath>

#define CENTS_FACTOR 2000000000
#define CENTS_MAX 2000

int main()
{
    long long a, b, c, d;
    long long product, sum;
    long long f1, f2;
    
    for (int a = 1; a + a + a + a <= CENTS_MAX; a++) {
        for (int b = a; a + b + b + b <= CENTS_MAX; b++) {
            for (int c = b; a + b + c + c <= CENTS_MAX; c++) {
                product = a * b * c;
                sum = a + b + c;
                
                if (product <= 1000000)
                    continue;

                f1 = sum * 1000000;
                f2 = product - 1000000;

                if (f1 % f2 != 0)
                    continue;

                d = f1 / f2;
                sum += d;
                product *= d;
                if (c > d || sum > CENTS_MAX || product > CENTS_FACTOR)
                    continue;

                printf("%.2f %.2f %.2f %.2f\n", a / 100., b / 100., c / 100., d / 100.);
            }
        }
    }
}
