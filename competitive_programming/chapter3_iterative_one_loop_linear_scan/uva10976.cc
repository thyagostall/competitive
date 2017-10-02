#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int k, x;
    while (cin >> k) {
        vector<pair<int, int>> solutions;
        for (int y = k + 1; y <= 2 * k; y++) {
            if ((y * k) % (y - k) == 0) {
                x = (y * k) / (y - k);
                solutions.push_back(make_pair(x, y));
            }
        }

        cout << solutions.size() << endl;
        for (auto &solution : solutions) 
            cout << "1/" << k << " = " << "1/" << solution.first << " + " << "1/" << solution.second << endl;
    }
}
