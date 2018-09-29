#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

ostream &operator<<(ostream &out, const vector<int> &v);
ostream &operator<<(ostream &out, const vector<vector<int>> &v);

vector<vector<int>> compute_bags(vector<int> &bag_sizes);
int compute_bag_qty(vector<int> &bag_sizes);

int main()
{
    int bag_qty, case_num = 0;

    while (cin >> bag_qty && bag_qty) {
        vector<int> bag_sizes(bag_qty, 0);
        for (int i = 0; i < bag_qty; i++) {
            cin >> bag_sizes[i];
        }

        if (case_num++) cout << endl;
        vector<vector<int>> bags = compute_bags(bag_sizes);
        cout << bags.size() << endl;
        cout << bags;
    }
}

ostream &operator<<(ostream &out, const vector<int> &v)
{
    for (int i = 0; i < v.size(); i++) {
        if (i) out << " ";
        out << v[i];
    }
    return out;
}

ostream &operator<<(ostream &out, const vector<vector<int>> &v)
{
    for (int i = 0; i < v.size(); i++) {
        out << v[i] << endl;
    }
    return out;
}

vector<vector<int>> compute_bags(vector<int> &bag_sizes)
{
    vector<vector<int>> bags;

    sort(bag_sizes.begin(), bag_sizes.end());

    int bag_qty = compute_bag_qty(bag_sizes);
    for (int i = 0; i < bag_qty; i++) {
        vector<int> bag;
        for (int j = i; j < bag_sizes.size(); j += bag_qty) {
            bag.push_back(bag_sizes[j]);
        }
        bags.push_back(bag);
    }
    return bags;
}

int compute_bag_qty(vector<int> &bag_sizes)
{
    int bag_qty = 1, current_streak = 1;
    for (int i = 1; i < bag_sizes.size(); i++) {
        if (bag_sizes[i] == bag_sizes[i - 1]) {
            bag_qty = max(++current_streak, bag_qty);
        } else {
            current_streak = 1;
        }
    }
    return bag_qty;
}
