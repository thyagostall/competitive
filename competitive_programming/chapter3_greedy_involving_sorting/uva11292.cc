#include <iostream>
#include <vector>
#include <algorithm>

#define DOOMED -1

using namespace std;

int compute_cost(vector<int> &head_sizes, vector<int> &knights_heights);

int main()
{
    int heads, knights;
    while (cin >> heads >> knights && heads && knights) {
        vector<int> head_sizes(heads, 0);
        vector<int> knights_heights(knights, 0);

        for (int i = 0; i < heads; i++) {
            cin >> head_sizes[i];
        }

        for (int i = 0; i < knights; i++) {
            cin >> knights_heights[i];
        }
        
        int cost = compute_cost(head_sizes, knights_heights);
        if (cost == DOOMED)
            cout << "Loowater is doomed!" << endl;
        else
            cout << cost << endl;
    }
}

int compute_cost(vector<int> &head_sizes, vector<int> &knights_heights)
{
    sort(head_sizes.begin(), head_sizes.end());
    sort(knights_heights.begin(), knights_heights.end());

    if (head_sizes.size() > knights_heights.size()) 
        return DOOMED;

    int cost = 0;
    for (int i = 0, j = 0; i < head_sizes.size(); i++, j++) {
        while (head_sizes[i] > knights_heights[j] && j < knights_heights.size()) j++;

        if (j >= knights_heights.size()) return DOOMED;

        cost += knights_heights[j];
    }
    return cost;
}
