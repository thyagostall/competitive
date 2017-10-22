#include <iostream>
#include <vector>

#define MAX 20

using namespace std;

bool primes[] = {true, true, true, true, false, true, false, true, false, false, false, true, false, true, false, false, false, true, false, true, false, false, false, true, false, false, false, false, false, true, false, true};

void print_vector(vector<int> &v)
{
    for (int i = 0; i < v.size(); i++) {
        if (i) cout << " ";
        cout << v[i];
    }
}

void print_results(vector<vector<int>> &results)
{
    for (auto &v: results) {
        print_vector(v);
        cout << endl;
    }
}

bool is_prime(int number)
{
    return primes[number];
}

bool is_valid(vector<int> &current)
{
    bool contained[MAX];
    for (int i = 0; i < MAX; i++) contained[i] = false;
    for (int i = 0; i < current.size(); i++) {
        if (contained[current[i]]) return false;
        contained[current[i]] = true;
    }
    for (int i = 1; i < current.size(); i++) {
        if (!is_prime(current[i - 1] + current[i])) return false;
    }
    return true;
}

void backtrack(int length, vector<int> &current, vector<vector<int>> &results)
{
    if (!is_valid(current)) return;

    if (current.size() == length && is_prime(current[0] + current[length - 1])) {
        results.push_back(current);
        return;
    }

    for (int i = 2; i <= length; i++) {
        current.push_back(i);
        backtrack(length, current, results);
        current.pop_back();
    }
}

int main()
{
    int case_number, length;

    case_number = 1;
    while (cin >> length) {
        vector<vector<int>> results;
        vector<int> current;

        current.push_back(1);
        backtrack(length, current, results);

        if (case_number > 1) cout << endl;
        cout << "Case " << case_number++ << ":" << endl;
        print_results(results);
    }
}
