#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

#define MAX 20

void printa(int *arr, int n)
{
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int test_cases, side, final_value, value;
    int board[MAX][MAX], column_order[MAX];

    cin >> test_cases;
    while (test_cases--) {
        cin >> side;
        for (int i = 0; i < side; i++) {
            column_order[i] = i;
            for (int j = 0; j < side; j++) {
                cin >> board[i][j];
            }
        }

        final_value = numeric_limits<int>::max();
        do {
            value = 0;
            for (int i = 0; i < side; i++) {
                value += board[i][column_order[i]];
            }
            final_value = min(final_value, value);
        } while (next_permutation(column_order, column_order + side));
        cout << final_value << endl;
    }
}
