#include <iostream>
#include <string>
#include <vector>

using namespace std;

int compute_minimum_scarecrow_quantity(const string &field);
bool should_be_placed(const string &field, vector<bool> &scarecrow_covering, int i);
void place_scarecrow(const string &field, vector<bool> &scarecrow_covering, int i);
bool is_fertile(const string &field, int i);

int main()
{
    int test_case_qty, field_size;
    string field;
    cin >> test_case_qty;
    for (int test_case = 1; test_case <= test_case_qty; test_case++) {
        cin >> field_size;
        cin >> field;

        cout << "Case " << test_case << ": " << compute_minimum_scarecrow_quantity(field) << endl;
    }
}

int compute_minimum_scarecrow_quantity(const string &field)
{    
    int scarecrow_qty = 0;
    vector<bool> scarecrow_covering(field.size() + 2, false);

    for (int i = 0; i < field.size(); i++) {
        if (should_be_placed(field, scarecrow_covering, i)) {
            scarecrow_qty++;
            place_scarecrow(field, scarecrow_covering, i);
        }
    }
    return scarecrow_qty;
}

bool should_be_placed(const string &field, vector<bool> &scarecrow_covering, int i)
{
    return (is_fertile(field, i) && !scarecrow_covering[i]);
}

void place_scarecrow(const string &field, vector<bool> &scarecrow_covering, int i)
{
    scarecrow_covering[i] = true;
    scarecrow_covering[i + 1] = true;
    scarecrow_covering[i + 2] = true;
}

bool is_fertile(const string &field, int i)
{
    return i < field.size()
        ? field[i] == '.'
        : true;
}

