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
        //cout << n << " " << p << endl;
        getline(cin, req);
        for (i = 0; i < n; i++) {
            getline(cin, req);
        //    cout << req << endl;
        }

        rmax = 0, dmin = numeric_limits<float>::max();
        while (p--) {
            getline(cin, prop);
            //cout << prop << endl;
            cin >> d >> r;
            //cout << d << " " << r << endl;
            getline(cin, req);
            for (i = 0; i < r; i++) {
                getline(cin, req);
         //       cout << req << endl;
            }

            if (r > rmax || r == rmax && d < dmin) {
                selected = prop;
                rmax = r, dmin = d;
            }
        }
       
        cout << "RFP #" << ++c << endl;
        cout << selected << endl << endl;
    }
    return 0;
}
