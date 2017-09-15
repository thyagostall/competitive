#include <vector>

class SegmentTree {
private:
    std::vector<int> tree, input;
    int size;

    int left(int p) 
    {
        return p << 1;
    }

    int right(int p) 
    {
        return (p << 1) + 1;
    }

    int build(int p, int l, int r) 
    {
        if (l != r) {
            int p1 = this->build(left(p), l, (l + r) / 2);
            int p2 = this->build(right(p), (l + r) / 2 + 1, r);

            return tree[p] = this->compute(p1, p2);
        } else {
            return tree[p] = this->next_leaf_value(p, l, r);
        }
    }

    int query(int p, int l, int r, int i, int j)
    {
        if (i > r || j < l) return out_of_bounds_value();
        if (l >= i && r <= j) return tree[p];

        int p1 = query(left(p), l, (l + r) / 2, i, j);
        int p2 = query(right(p), (l + r) / 2 + 1, r, i, j);

        return compute(p1, p2);
    }
protected:
    int compute(int i, int j)
    {
        return i + j;
    }

    int next_leaf_value(int p, int l, int r)
    {
        return input[l];
    }

    int out_of_bounds_value()
    {
        return 0;
    }
public:
    SegmentTree(const std::vector<int> input)
    {
        this->size = input.size();
        this->input = input;       
        tree.assign(4 * size, 0);
        build(1, 0, size - 1);
    }

    int query(int i, int j)
    {
        return this->query(1, 0, size - 1, i, j);
    }
};

#ifndef TESTS
#define TESTS

#include <iostream>

using namespace std;

SegmentTree provide_tree()
{
    int arr[] = {18, 17, 13, 19, 15, 11, 20};
    vector<int> input(arr, arr + 7);
    return SegmentTree(input);
}

void test_sum_input_root()
{
    SegmentTree t = provide_tree();
    if (t.query(0, 6) == 113) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_sum_input_left_branch()
{
    SegmentTree t = provide_tree();
    if (t.query(0, 3) == 67) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_sum_input_right_branch()
{
    SegmentTree t = provide_tree();
    if (t.query(4, 6) == 46) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_sum_input_intersection()
{
    SegmentTree t = provide_tree();
    if (t.query(3, 4) == 34) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_sum_input_only_one_index()
{
    SegmentTree t = provide_tree();
    if (t.query(4, 4) == 15) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

int main()
{
    test_sum_input_root();
    test_sum_input_left_branch();
    test_sum_input_right_branch();
    test_sum_input_intersection();
    test_sum_input_only_one_index();
}

#endif
