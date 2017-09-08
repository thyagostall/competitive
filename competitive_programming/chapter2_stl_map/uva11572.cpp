#include <iostream>
#include <map>

using namespace std;

int main()
{
    int test_cases, n, buff;
    
    cin >> test_cases;
    while (test_cases--) {
        cin >> n;

        map<int, int> unique;
        int first = 1, current = 1;
        int best = 0;

        while (n--) {
            cin >> buff;
            unique[buff] = unique[buff] ? unique[buff] : current;
            if (unique[buff] != current) {
                while (unique[buff] >= first) first++;
                unique[buff] = current;
            }
            best = max(best, current - first + 1);
            current++;
        }
        cout << best << endl;
    }
}
