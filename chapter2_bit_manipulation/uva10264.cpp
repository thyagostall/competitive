#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    int qty, n;

    while (cin >> n) {
        qty = pow(2, n);

        vector<int> powers(qty, 0);
        vector<int> potencies(qty, 0);
        
        for (int i = 0; i < qty; i++) {
            cin >> powers[i];
        }

        for (int i = 0; i < qty; i++) {
            potencies[i] = powers[i];
            for (int j = 0; j < n; j++) {
                potencies[i] += powers[i ^ 1 << j];
            }
        }
        
        int max_potency = 0;
        for (int i = 0; i < qty; i++) {
            for (int j = 0; j < n; j++) {
                max_potency = max(max_potency, potencies[i] + potencies[i ^ 1 << j] - powers[i] - powers[i ^ 1 << j]);
            }
        }
        cout << max_potency << endl;
    }
}
