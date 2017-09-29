#include <vector>
#include <iostream>

using namespace std;

class FenwickTree
{
public:
    FenwickTree(int n): size(n + 1), table(size)
    {
        table.assign(size, 0);
        values.assign(size, false);
    }

    void update(int i, bool new_value)
    {
        if (new_value == values[i])
            return;

        values[i] = new_value;

        int delta = new_value ? 1 : -1;
        while (i < size) {
            table[i] += delta;
            i += lowest_one_bit(i);
        }
    }

    void toggle(int i)
    {
        values[i] = !values[i];

        int delta = values[i] ? 1 : -1;
        while (i < size) {
            table[i] += delta;
            i += lowest_one_bit(i);
        }
    }

    int sum(int i)
    {
        int result = 0;
        while (i) {
            result += table[i];
            i -= lowest_one_bit(i);
        }
        return result;
    }

    int range_sum(int i, int j)
    {
        return sum(j) - sum(i - 1);
    }
private:
    int size;
    std::vector<int> table;
    std::vector<bool> values;

    int lowest_one_bit(int i)
    {
        return i & -i;
    }
};

#ifndef TESTS
#define TESTS

#include <iostream>

using namespace std;

void test_create_empty_tree()
{
    FenwickTree ft(10);
    cout << "✔ Test passed" << endl;
}

void test_update_first()
{
    FenwickTree ft(10);
    ft.update(1, true);
    int result = ft.range_sum(1, 1);
    if (result == 1) {
        cout << "✔ Test passed" << endl;
    } else {
        cout << "✘ Test failed" << endl;
    }
}

void test_update_all_values()
{
    FenwickTree ft(10);
    for (int i = 1; i <= 10; i++) {
        ft.update(i, true);
    }
    int result = ft.range_sum(1, 10);
    if (result == 10) {
        cout << "✔ Test passed" << endl;
    } else {
        cout << "✘ Test failed" << endl;
    }
}

void test_update_no_value()
{
    FenwickTree ft(10);
    int result = ft.range_sum(1, 10);
    if (result == 0) {
        cout << "✔ Test passed" << endl;
    } else {
        cout << "✘ Test failed" << endl;
    }
}

void test_update_only_even()
{
    FenwickTree ft(10);
    for (int i = 1; i <= 10; i++) {
        if (i % 2) continue;
        ft.update(i, true);
    }
    int result = ft.range_sum(1, 10);
    if (result == 5) {
        cout << "✔ Test passed" << endl;
    } else {
        cout << "✘ Test failed" << endl;
    }
}

void test_update_only_odd()
{
    FenwickTree ft(10);
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) continue;
        ft.update(i, true);
    }
    int result = ft.range_sum(1, 10);
    if (result == 5) {
        cout << "✔ Test passed" << endl;
    } else {
        cout << "✘ Test failed" << endl;
    }
}

void test_toggle_to_false()
{
    FenwickTree ft(10);
    ft.update(1, true);
    ft.toggle(1);
    int result = ft.range_sum(1, 10);
    if (result == 0) {
        cout << "✔ Test passed" << endl;
    } else {
        cout << "✘ Test failed" << endl;
    }
}

void test_toggle_to_true()
{
    FenwickTree ft(10);
    ft.toggle(1);
    int result = ft.range_sum(1, 10);
    if (result == 1) {
        cout << "✔ Test passed" << endl;
    } else {
        cout << "✘ Test failed" << endl;
    }
}

void test_toggle_everything_to_true()
{
    FenwickTree ft(10);
    for (int i = 1; i <= 10; i++) {
        ft.toggle(i);
    }
    int result = ft.range_sum(1, 10);
    if (result == 10) {
        cout << "✔ Test passed" << endl;
    } else {
        cout << "✘ Test failed" << endl;
    }
}

void test_toggle_everything_to_false()
{
    FenwickTree ft(10);
    for (int i = 1; i <= 10; i++) {
        ft.update(i, true);
    }
    for (int i = 1; i <= 10; i++) {
        ft.toggle(i);
    }
    int result = ft.range_sum(1, 10);
    if (result == 0) {
        cout << "✔ Test passed" << endl;
    } else {
        cout << "✘ Test failed" << endl;
    }
}

void test_toggle_alternate()
{
    FenwickTree ft(10);
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) continue;
        ft.update(i, true);
    }
    for (int i = 1; i <= 10; i++) {
        if (i % 2 != 0) continue;
        ft.toggle(i);
    }
    int result = ft.range_sum(1, 10);
    if (result == 10) {
        cout << "✔ Test passed" << endl;
    } else {
        cout << "✘ Test failed" << endl;
    }
}

int main()
{
    test_create_empty_tree();
    test_update_first();
    test_update_all_values();
    test_update_no_value();
    test_update_only_even();
    test_update_only_odd();
    test_toggle_to_false();
    test_toggle_to_true();
    test_toggle_everything_to_true();
    test_toggle_everything_to_false();
    test_toggle_alternate();
}

#endif
