#include <iostream>
#include <array>
#include <algorithm>

#define MAX 105

using namespace std;

typedef struct {
    int driver_qty, max_hours, hour_rate;
    array<int, MAX> morning_lengths, evening_lengths;
} DriversConstraints;

int compute_minimum_overtime_payment(DriversConstraints &constraints);
int compute_overtime(int total_hours, int max_hours);

int main()
{
    DriversConstraints constraints;

    while (cin >> constraints.driver_qty >> constraints.max_hours >> constraints.hour_rate && constraints.driver_qty) {
        for (int i = 0; i < constraints.driver_qty; i++) {
            cin >> constraints.morning_lengths[i];
        }

        for (int i = 0; i < constraints.driver_qty; i++) {
            cin >> constraints.evening_lengths[i];
        }

        cout << compute_minimum_overtime_payment(constraints) << endl;
    }
}

int compute_minimum_overtime_payment(DriversConstraints &constraints)
{
    sort(constraints.morning_lengths.begin(), constraints.morning_lengths.begin() + constraints.driver_qty);
    sort(constraints.evening_lengths.begin(), constraints.evening_lengths.begin() + constraints.driver_qty);

    int overtime, minimum_overtime_payment = 0;
    int i, j, d = constraints.driver_qty;
    for (i = 0, j = d - 1; i < d && j >= 0; i++, j--) {
        overtime = compute_overtime(constraints.morning_lengths[i] + constraints.evening_lengths[j], constraints.max_hours);
        minimum_overtime_payment += overtime * constraints.hour_rate;
    }

    return minimum_overtime_payment;
}

int compute_overtime(int total_hours, int max_hours)
{
    return max(total_hours - max_hours, 0);
}
