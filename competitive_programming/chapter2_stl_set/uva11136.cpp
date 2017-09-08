#include <iostream>
#include <set>

using namespace std;

typedef unsigned long long ull;

class Urn: public multiset<ull>
{
public:
    ull min() {
        multiset<ull>::iterator first = this->begin();
        ull result = *first;
        this->erase(first);
        return result;
    }

    ull max() {
        multiset<ull>::iterator last = prev(this->end());
        ull result = *last;
        this->erase(last);
        return result;
    }
};

int main()
{
    ull days, buff, bills;

    while (cin >> days && days) {
        ull cost = 0;
        Urn urn;

        while (days--) {
            cin >> bills;
            while (bills--) {
                cin >> buff;
                urn.insert(buff);
            }
            cost += urn.max() - urn.min();
        }
        cout << cost << endl;
    }
}
