#include <iostream>
#include <vector>

using namespace std;

int compute_streak(const vector<int> &bets);

istream &operator>>(istream &in, vector<int> &v);
ostream &operator<<(ostream &out, vector<int> v);

int main()
{
    int bet_qty;
    while (cin >> bet_qty && bet_qty) {
        vector<int> bets(bet_qty);
        cin >> bets;
        
        int streak = compute_streak(bets);
        if (streak)
            cout << "The maximum winning streak is " << streak << "." << endl;
        else
            cout << "Losing streak." << endl;
    }
}

int compute_streak(const vector<int> &bets)
{
    int max_streak = 0, current_streak;
    for (auto bet : bets) {
        current_streak += bet;
        max_streak = max(current_streak, max_streak);
        if (current_streak < 0) current_streak = 0;
    }
    return max_streak;
}

istream &operator>>(istream &in, vector<int> &v)
{
    for (auto &i : v) 
        in >> i;
    return in;
}

ostream &operator<<(ostream &out, vector<int> &v)
{
    for (int i = 0; i < v.size(); i++) {
        if (i) out << " ";
        out << v[i]; 
    }
    return out;
}

