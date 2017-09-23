#include <vector>

using namespace std;

class FenwickTree
{
public:
    FenwickTree(int size): table(size)
    {
        this->size = size;
        table.assign(size, 0);
    }

    void update(int i, int delta)
    {
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
    ft.update(1, 10);
    int result = ft.range_sum(1, 1);
    if (result == 10) {
        cout << "✔ Test passed" << endl;
    } else {
        cout << "✘ Test failed" << endl;
    }
}

void test_range_sum()
{
    FenwickTree ft(10);
    ft.update(1, 10);
    int result = ft.range_sum(1, 9);
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
    test_range_sum();
}

#endif
