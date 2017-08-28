#include <cstdio>
#include <climits>

using namespace std;

const int INFINITY = INT_MAX;

int main()
{
    int M, N, Mc, Mn, m;
    float D, O, C, Dc, Dn, P;

    while (scanf("%d %f %f %d", &M, &D, &O, &N) && M >= 0) {
        C = O + D; 
        P = O / M;

        scanf("%d %f", &Mn, &Dn), N--;
        for (m = 0; m <= M; m++) {
            if (m == Mn) {
                Mc = Mn, Dc = Dn;
                Mn = INFINITY, Dn = 0;
                if (N-- > 0) scanf("%d %f", &Mn, &Dn);
            }

            if (m > 0) O = O - P;
            C = C * (1 - Dc);

            if (O < C) break;
        }

        if (m == 1)
            printf("%d month\n", m);
        else
            printf("%d months\n", m);
    }
}
