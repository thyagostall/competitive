#include <iostream>

#define MAX 50
#define SIZE 6

using namespace std;

int main()
{
    int number_qty, buff;
    int numbers[MAX];
    bool first = true;

    while (cin >> number_qty && number_qty) {
        if (!first) cout << endl;
        first = false;

        for (int i = 0; i < number_qty; i++) {
            cin >> numbers[i];
        }

        for (int i = 0; i <= number_qty - SIZE; i++)
        for (int j = i + 1; j <= number_qty - SIZE + 1; j++)
        for (int k = j + 1; k <= number_qty - SIZE + 2; k++)
        for (int l = k + 1; l <= number_qty - SIZE + 3; l++)
        for (int m = l + 1; m <= number_qty - SIZE + 4; m++)
        for (int n = m + 1; n <= number_qty - SIZE + 5; n++)
            cout << numbers[i] << " "
                 << numbers[j] << " "
                 << numbers[k] << " "
                 << numbers[l] << " "
                 << numbers[m] << " "
                 << numbers[n] << endl;
    }
}
