#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int q, n, m;
    string p;

    cin >> q;
    while (q--) {
        cin >> p >> m >> n;

        if (p == "r" || p == "Q") {
            cout << fmin(m, n) << endl;
        } else if (p == "k") {
            cout << ceil(m * n / 2.) << endl;
        } else if (p == "K") {
            cout << ceil(m / 2.) * ceil(n / 2.) << endl;
        }
    }
}
