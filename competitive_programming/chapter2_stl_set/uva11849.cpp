#include <iostream>
#include <unordered_set>

using namespace std;

int main()
{
    int jack_qty, jill_qty, buff;
    while (cin >> jack_qty >> jill_qty && (jack_qty || jill_qty)) {
        int count = 0;
        unordered_set<int> cds_jack;

        while (jack_qty--) {
            cin >> buff;
            cds_jack.insert(buff);
        }

        while (jill_qty--) {
            cin >> buff;
            if (cds_jack.find(buff) != cds_jack.end()) count++;
        }
        cout << count << endl;
    }
}
