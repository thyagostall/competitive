#include <iostream>
#include <vector>

#define EMPTY -1
#define COIN_QTY 5
#define CHANGE_RANGE 30001

using namespace std;

unsigned long count_possible_ways(const int type, const int change);

vector<int> coins = {1, 5, 10, 25, 50};
vector<vector<unsigned long>> cache(COIN_QTY, vector<unsigned long>(CHANGE_RANGE, EMPTY));

int main()
{
    int change;
    while (cin >> change) {
        unsigned long ways = count_possible_ways(0, change);

        if (ways == 1) {
            cout << "There is only 1 way to produce "
                 << change
                 << " cents change." << endl;
        } else {
            cout << "There are " 
                 << ways 
                 << " ways to produce " 
                 << change 
                 << " cents change." << endl;
        }
    }
}

unsigned long count_possible_ways(const int type, const int change)
{
    if (change == 0) 
        return 1;

    if (change < 0 || type >= coins.size()) 
        return 0;

    return cache[type][change] != EMPTY
        ? cache[type][change]
        : cache[type][change] = count_possible_ways(type, change - coins[type]) + count_possible_ways(type + 1, change);
}

