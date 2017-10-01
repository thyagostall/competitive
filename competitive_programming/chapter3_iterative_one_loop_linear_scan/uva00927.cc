#include <iostream>
#include <vector>

using namespace std;

class Polynomial: public vector<int>
{
public:
    using vector::operator[];

    Polynomial(int coefs[], int i):
        vector<int>(coefs, coefs + i + 1)
    {
        this->i = i;
    }

    long long compute(int n)
    {
        long long result = 0;
        for (int x = 0; x <= i; x++) {
            result += operator[](x) * pow(n, x);
        }
        return result;
    }
private:
    int i;

    long long pow(int base, int exp)
    {
        if (exp == 0) return 1;

        long long result = base;
        while (--exp) {
            result *= base;
        }
        return result;
    }
};

int main()
{
    int test_cases, i, d, k, n;
    int coef[21];
    long long last;

    cin >> test_cases;
    while (test_cases--) {
        cin >> i;
        for (int n = 0; n <= i; n++) {
            cin >> coef[n];
        }
        Polynomial a(coef, i);
        cin >> d >> k;
        
        i = 0, n = 1;
        while (i < k) {
            last = a.compute(n);
            for (int j = 0; j < n * d; j++) {
                i++;
                if (i >= k) break;
            }
            n++;
        }
        cout << last << endl;
    }
}
