#include <iostream>

#define MAX 20
#define LAST_SUBSET 1048575

using namespace std;

int compute_sum(int *array, int array_size, int elements)
{
    int result = 0;
    for (int i = 0; i < array_size; i++) {
        if (1 << i & elements) {
            result += array[i];
        }
    }
    return result;
}

int main()
{
    int test_cases, length, bar_quantity, candidate, subset;
    int bars[MAX];

    cin >> test_cases;
    while (test_cases--) {
        cin >> length >> bar_quantity;

        for (int i = 0; i < bar_quantity; i++)
            cin >> bars[i];

        subset = 0;
        do {
            candidate = compute_sum(bars, bar_quantity, subset++);
        } while (subset <= LAST_SUBSET && candidate != length);

        if (candidate == length)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}
