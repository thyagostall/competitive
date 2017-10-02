#include <iostream>

#define MAX_SIZE 1000

using namespace std;

int main()
{
    int test_cases, size, daily_sales[MAX_SIZE];
    cin >> test_cases;
    while (test_cases--) {
        cin >> size;
        for (int i = 0; i < size; i++) {
            cin >> daily_sales[i];
        }
        int result = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < i; j++) {
                if (daily_sales[j] <= daily_sales[i]) result++;
            }
        }
        cout << result << endl;
    }
}
