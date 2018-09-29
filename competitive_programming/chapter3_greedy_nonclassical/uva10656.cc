#include <iostream>
#include <vector>

using namespace std;

ostream &operator<<(ostream &out, vector<int> v);

vector<int> compute_maximum_subsequence(vector<int> &sequence);

int main()
{
    int quantity;
    while (cin >> quantity && quantity) {
        vector<int> sequence(quantity, 0);
        for (int i = 0; i < quantity; i++)
            cin >> sequence[i];
        cout << compute_maximum_subsequence(sequence) << endl;
    }
}

ostream &operator<<(ostream &out, vector<int> v)
{
    for (int i = 0; i < v.size(); i++) {
        if (i) out << " ";
        out << v[i];
    }
    return out;
}

vector<int> compute_maximum_subsequence(vector<int> &sequence)
{
    vector<int> maximum_subsequence;
    int sum = 0;
    for (int i = 0; i < sequence.size(); i++) {
        if (sum + sequence[i] > sum) {
            maximum_subsequence.push_back(sequence[i]);
            sum += sequence[i];
        }
    }
    if (sum == 0) {
        maximum_subsequence.push_back(0);
    }
    return maximum_subsequence;
}
