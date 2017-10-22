#include <iostream>
#include <vector>

using namespace std;

bool is_valid(vector<int> &balance)
{
    for (int i = 0; i + 5 <= balance.size(); i++) {
        int sum = 0;
        for (int j = i; j < i + 5; j++) {
            sum += balance[j];
        }

        if (sum >= 0) {
            return false;
        }
    }
    return true;
}

int sum(vector<int> &balance)
{
    int result = 0;
    for (auto &i : balance)
        result += i;
    return result;
}

int calculate(vector<int> balance, int surplus, int deficit)
{
    if (!is_valid(balance))
        return -1;

    if (balance.size() == 12)
        return sum(balance);

    balance.push_back(surplus);
    int candidate = calculate(balance, surplus, deficit);
    balance.pop_back();
    balance.push_back(-deficit);
    candidate = max(candidate, calculate(balance, surplus, deficit));
    balance.pop_back();

    return candidate;
}

int main()
{
    int surplus, deficit, result;
    while (cin >> surplus >> deficit) {
        vector<int> balance;
        result = calculate(balance, surplus, deficit);
        if (result > 0) cout << result << endl;
        else            cout << "Deficit" << endl;
    }
}
