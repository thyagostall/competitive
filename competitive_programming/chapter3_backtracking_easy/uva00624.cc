#include <iostream>
#include <vector>

#define MAX 20

using namespace std;

bool is_best(int current_sum, int best_sum, int goal)
{
    if (current_sum > goal) return false;

    return (goal - current_sum < goal - best_sum);
}

void backtrack(
        int *items, int size, int goal, 
        vector<int> &path, int current_sum, int start, 
        vector<int> &best_path, int &best_sum)
{
    if (current_sum > goal)
        return;

    if (is_best(current_sum, best_sum, goal)) {
        best_sum = current_sum;
        best_path = path;
    }

    for (int i = start; i < size; i++) {
        path.push_back(items[i]);
        backtrack(items, size, goal, path, current_sum + items[i], i + 1, best_path, best_sum);
        path.pop_back();
    }
}

void print_result(vector<int> &path, int sum)
{
    for (auto &item : path)
        cout << item << " ";
    cout << "sum:" << sum << endl;
}

int main()
{
    int goal, track_quantity;
    int items[MAX];

    while (cin >> goal) {
        cin >> track_quantity;
        for (int i = 0; i < track_quantity; i++)
            cin >> items[i];

        vector<int> best_path, path;
        int best_sum = 0;
        backtrack(items, track_quantity, goal, path, 0, 0, best_path, best_sum);
        print_result(best_path, best_sum);
    }
}
