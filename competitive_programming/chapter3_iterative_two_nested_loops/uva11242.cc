#include <iostream>
#include <iomanip>
#include <algorithm>

#define MAX_SIZE 15

using namespace std;

double division(int a, int b)
{
    return (double)a / (double)b;
}

double max(double a, double b)
{
    return a > b ? a : b;
}

int main()
{
    int front[MAX_SIZE], rear[MAX_SIZE];
    int front_qty, rear_qty, current;
    double ratios[MAX_SIZE * MAX_SIZE];
    double result;

    while (cin >> front_qty >> rear_qty && front_qty) {
        for (int i = 0; i < front_qty; i++) {
            cin >> front[i];
        }
        for (int i = 0; i < rear_qty; i++) {
            cin >> rear[i];
        }

        current = 0;
        for (int i = 0; i < front_qty; i++) {
            for (int j = 0; j < rear_qty; j++) {
                ratios[current++] = division(rear[j], front[i]);
            }
        }
        
        sort(ratios, ratios + current);

        result = 0;
        for (int i = 1; i < current; i++) {
            result = max(ratios[i] / ratios[i - 1], result);
        }

        cout << fixed << setprecision(2) << result << endl;
    }
}
