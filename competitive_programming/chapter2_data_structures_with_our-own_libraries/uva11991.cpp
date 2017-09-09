#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main()
{
    int n, m, buff, k, v;
    while (cin >> n >> m) {
        unordered_map<int, vector<int>> occurrences;
        for (int i = 1; i <= n; i++) {
            cin >> buff;
            occurrences[buff].push_back(i);
        }
        while (m--) {
            cin >> k >> v;
            if (k <= occurrences[v].size()) {
                cout << occurrences[v][k - 1] << endl;
            } else {
                cout << 0 << endl;
            }
        }
    }
}
