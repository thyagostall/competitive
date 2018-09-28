#include <iostream>
#include <vector>

using namespace std;

int compute(vector<int> &coin_values);

int main()
{
    int case_qty, coin_qty, buffer;

    cin >> case_qty;
    while (case_qty--) {
        cin >> coin_qty;
        vector<int> coin_values(coin_qty, 0);
        for (int i = 0; i < coin_qty; i++) {
            cin >> coin_values[i];
        }
        cout << compute(coin_values) << endl;
    }
}

int compute(vector<int> &coin_values)
{
    int sum = 0;
    int coin_qty = 1;
    for (int i = 0; i < coin_values.size() - 1; i++) {
        if (sum + coin_values[i] < coin_values[i + 1]) {
            sum += coin_values[i];
            coin_qty++;
        }
    }
    return coin_qty;
}
