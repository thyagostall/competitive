#include <iostream>
#include <limits>

using namespace std;

int main()
{
    int n, p, r, i, c, rmax;
    float d, dmin;
    string prop, req, selected;

    c = 0;
    while (cin >> n >> p && n > 0 && p > 0) {
        cin.ignore();
        for (i = 0; i < n; i++) {
            getline(cin, req);
        }

        rmax = 0, dmin = numeric_limits<float>::max();
        while (p--) {
            getline(cin, prop);
            cin >> d >> r;
            cin.ignore();
            for (i = 0; i < r; i++) {
                getline(cin, req);
            }

            if (r > rmax || r == rmax && d < dmin) {
                selected = prop;
                rmax = r, dmin = d;
            }
        }
      
        if (c) cout << endl;
        cout << "RFP #" << ++c << endl;
        cout << selected << endl;
    }
    return 0;
}
