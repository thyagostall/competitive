#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    while (cin >> n && n) {
        map<vector<int>, int> frequencies;
        while (n--) {
            vector<int> combination(5, 0);
            for (int i = 0; i < 5; i++) {
                cin >> combination[i];
            }
            sort(begin(combination), end(combination));

            frequencies[combination]++;
        }

        int most_frequent = 0;
        for (auto i : frequencies) {
            most_frequent = max(i.second, most_frequent);
        }
        
        int count_most_frequent = 0;
        for (auto i : frequencies) {
            if (i.second == most_frequent) count_most_frequent += i.second;
        }

        cout << count_most_frequent << endl;
    }
}
