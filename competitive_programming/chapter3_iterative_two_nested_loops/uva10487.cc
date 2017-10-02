#include <iostream>
#include <limits>

#define MAX_SIZE 1000

using namespace std;

int closest_sum(int elements[], int size, int query)
{
    int diff = numeric_limits<int>::max();
    int best;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            int sum = elements[i] + elements[j];
            int current_diff = abs(sum - query);
            if (current_diff < diff) {
                diff = current_diff;
                best = sum;
            }
        }
    }
    return best;
}

int main()
{
    int size, queries, query, test_case = 0;
    int elements[MAX_SIZE];

    while (cin >> size && size) {
        for (int i = 0; i < size; i++) {
            cin >> elements[i];
        }
        cin >> queries;
        cout << "Case " << ++test_case << ":" << endl;
        while (queries--) {
            cin >> query;
            cout << "Closest sum to " 
                 << query
                 << " is "
                 << closest_sum(elements, size, query)
                 << "." << endl;
        }
    }
}
