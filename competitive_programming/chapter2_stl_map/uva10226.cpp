#include <map>
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int test_cases;
    string buff;
   
    cin >> test_cases;
    getline(cin, buff);
    getline(cin, buff);
    
    while (test_cases--) {
        map<string, int> frequencies;
        int total = 0;

        while (getline(cin, buff) && buff != "") {
            frequencies[buff]++;
            total++;
        }

        for (auto &tree : frequencies) {
            cout << tree.first << " ";
            cout << fixed << setprecision(4);
            cout << (double) tree.second / total * 100 << endl;
        }
        if (test_cases) cout << endl;
    }
}
