#include <iostream>
#include <map>

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
    int result = 0;
    for (int i = 1; i <= mask; i <<= 1) {
        if (mask & i) {
            result += value[i];
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

int sum_intersections(map<int, int> &intersections, int mask)
{
    int count, result = 0;
    for (auto &intersection : intersections) {
        count = count_bits(intersection.first & mask);
        if (intersection.second && count > 1) {
            result += (count - 1) * intersection.second;
        }
    }
    return result;
}

int main()
{
    int total, installed, quantity, test_case, max_value, max_subset,
        intersection_qty, intersection, intersection_value, current,
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
        cin >> intersection_qty;
        map<int, int> intersections;
        while (intersection_qty--) {
            cin >> quantity;
            intersection = 0;
            while (quantity--) {
                cin >> temp;
                intersection |= (1 << temp - 1);
            }
            cin >> intersection_value;
            intersections[intersection] += intersection_value;
        }

        max_subset = max_value = 0;
        for (int i = 1; i <= (1 << total); i++) {
            if (count_bits(i) != installed)
                continue;

            current = sum_sets(towers, i) - sum_intersections(intersections, i);
            if (current == max_value) {
                for (int j = 0; j < total; j++) {
                    int current_bit = i & (1 << j);
                    int max_bit = max_subset & (1 << j);

                    if (current_bit != max_bit) {
                        if (current_bit > 0) {
                            max_value = current;
                            max_subset = i;
                        }
                        break;
                    }
                }
            } else if (current > max_value) {
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
