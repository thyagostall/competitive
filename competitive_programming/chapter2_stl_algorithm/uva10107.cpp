#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    vector<int> values;
    int number;
    while (cin >> number) {
        values.push_back(number);
        nth_element(values.begin(), values.begin() + values.size() / 2, values.end());
        
        int index = values.size() / 2;
        if (values.size() % 2) {
            cout << values[index] << endl;
        } else {
            nth_element(values.begin(), values.begin() + values.size() / 2 - 1, values.end());
            cout << (values[index - 1] + values[index]) / 2 << endl;
        }
    }
}
