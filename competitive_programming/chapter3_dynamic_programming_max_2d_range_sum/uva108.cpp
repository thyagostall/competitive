#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef vector<vector<int>> vector_int_2d;

vector_int_2d &precompute_sums(vector_int_2d &values);
int compute_maximum_subsum(vector_int_2d &values);
int subsum(vector_int_2d &values, int i, int j, int k, int l);

istream &operator>>(istream &in, vector_int_2d &values);

int main()
{
    int size;
    while (cin >> size) {
        vector_int_2d values(size, vector<int>(size, 0));

        cin >> values;
        values = precompute_sums(values);
        cout << compute_maximum_subsum(values) << endl;
    }
}

vector_int_2d &precompute_sums(vector_int_2d &values)
{
    for (int i = 0; i < values.size(); i++) {
        for (int j = 0; j < values.size(); j++) {
            if (i)
                values[i][j] += values[i - 1][j];
            if (j)
                values[i][j] += values[i][j - 1];
            if (i && j)
                values[i][j] -= values[i - 1][j - 1];
        }
    }
    return values;
}

int compute_maximum_subsum(vector_int_2d &values)
{
    int maximum_subsum = numeric_limits<int>::min();
    for (int i = 0; i < values.size(); i++) {
        for (int j = 0; j < values.size(); j++) {
            for (int k = i; k < values.size(); k++) {
                for (int l = j; l < values.size(); l++) {
                    maximum_subsum = max(maximum_subsum, subsum(values, i, j, k, l));
                }
            }
        }
    }
    return maximum_subsum;
}

int subsum(vector_int_2d &values, int i, int j, int k, int l)
{
    int result = values[k][l];
    if (i) result -= values[i - 1][l];
    if (j) result -= values[k][j - 1];
    if (i && j) result += values[i - 1][j - 1];
    return result;
}

istream &operator>>(istream &in, vector_int_2d &values)
{
    for (auto &rows : values)
        for (auto &element : rows)
            in >> element;
    return in;
}
