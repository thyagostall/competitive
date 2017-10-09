#include <iostream>
#include <bitset>

#define MAX 1048577

using namespace std;

int count_bits(int i)
{
    int result = 0;
    while (i) {
        if (i & 1) result++;
        i = i >> 1;
    }
    return result;
}

int sum_sets(int value[MAX], int mask)
{
    int count, result = 0;
    for (int i = 1; i <= mask; i++) {
        count = count_bits(i);
        if ((i & mask) == i) {
            if (count % 2) {
                result += value[i];
            } else {
                result -= value[i];
            }
        }
    }
    return result;
}

string calc_subsets(int mask)
{
    string result = "";
    int temp, nth;

    temp = nth = 1;
    while (temp <= mask) {
        if (temp & mask) {
            if (result.length() > 0) {
                result += " ";
            }
            result += to_string(nth);
        }
        nth++;
        temp = temp << 1;
    }
    return result;
}

int main()
{
    int total, installed, quantity, test_case, max_value, max_subset,
        intersections, intersection, intersection_value, current,
        temp;
    int towers[MAX];

    test_case = 0;
    while (cin >> total >> installed && total && installed) {
        for (int i = 0; i <= (1 << total); i++) {
            towers[i] = 0;
        }

        for (int i = 0; i < total; i++) {
            cin >> towers[1 << i];
        }
        cin >> intersections;
        while (intersections--) {
            cin >> quantity;
            intersection = 0;
            while (quantity--) {
                cin >> temp;
                intersection |= (1 << temp - 1);
            }
            cin >> intersection_value;
            towers[intersection] += intersection_value;
        }

        max_subset = max_value = 0;
        for (int i = 1; i <= (1 << total); i++) {
            if (count_bits(i) != installed) 
                continue;

            current = sum_sets(towers, i);
            if (current > max_value) {
                max_value = current;
                max_subset = i;
            }
        }

        cout << "Case Number  " << ++test_case << endl;
        cout << "Number of Customers: " << max_value << endl;
        cout << "Locations recommended: " << calc_subsets(max_subset) << endl;
        cout << endl;
    }
}
