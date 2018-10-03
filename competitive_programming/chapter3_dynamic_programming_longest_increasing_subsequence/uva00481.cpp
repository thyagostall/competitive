#include <iostream>
#include <vector>
#include <algorithm>

#define FIRST -1

using namespace std;

istream &operator>>(istream &in, vector<int> &v);
ostream &operator<<(ostream &out, vector<int> v);

vector<int> lis(vector<int> &sequence);
int get_correct_position(const vector<int> &elements, const int size, const int element);
int get_previous_index(const vector<int> &ids, const int index);
vector<int> create_sequence(const vector<int> &sequence, const vector<int> &previous, const int last_element);

int main()
{
    vector<int> sequence;
    cin >> sequence;
    cout << lis(sequence);
}

vector<int> lis(vector<int> &sequence)
{
    vector<int> temp(sequence.size(), 0);
    vector<int> ids(sequence.size(), 0);
    vector<int> previous(sequence.size(), 0);

    int current_lis = 0, last_element_lis = 0;
    for (int i = 0; i < sequence.size(); i++) {
        int correct_position = get_correct_position(temp, current_lis, sequence[i]);
        temp[correct_position] = sequence[i];
        ids[correct_position] = i;
        previous[i] = get_previous_index(ids, correct_position);
        if (correct_position + 1 > current_lis) {
            current_lis = correct_position + 1;
            last_element_lis = i;
        }
    }

    return create_sequence(sequence, previous, last_element_lis);
}

int get_correct_position(const vector<int> &elements, const int size, const int element)
{
    return lower_bound(elements.begin(), elements.begin() + size, element) - elements.begin();
}

int get_previous_index(const vector<int> &ids, const int index)
{
    return index
        ? ids[index - 1]
        : FIRST;
}

vector<int> create_sequence(const vector<int> &sequence, const vector<int> &previous, const int last_element)
{
    vector<int> result;
    for (int i = last_element; i > FIRST; i = previous[i]) {
        result.push_back(sequence[i]);
    }
    reverse(result.begin(), result.end());
    return result;
}

istream &operator>>(istream &in, vector<int> &v)
{
    int buffer;
    while (in >> buffer)
        v.push_back(buffer);
    return in;
}

ostream &operator<<(ostream &out, vector<int> v)
{
    out << v.size() << endl;
    out << "-" << endl;
    for (auto i : v)
        out << i << endl;
    return out;
}
