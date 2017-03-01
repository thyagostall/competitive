#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int m, n, t, result, v1, v2;
    while (cin >> m >> n && (m || n)) {
        if (m < n) {
            v1 = m, v2 = n;
        } else {
            v1 = n, v2 = m;
        }

        if (v1 == 1) {
            result = v2;
        } else if (v1 == 2) {
            if ((v2 - 1) % 4)
                result = ceil(v2 / 4.) * 4;
            else
                result = ceil(v2 / 2.) * 2;
        } else {
            result = ceil(m * n / 2.);
        }
        cout << result << " knights may be placed on a " << m << " row " << n << " column board." << endl;
    }
}
