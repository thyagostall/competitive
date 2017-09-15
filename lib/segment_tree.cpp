#include <vector>

class SegmentTree {
private:
    static const int OUT_OF_BOUNDS = -1;
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

    bool compare(int a, int b) 
    {
        return a <= b;
    }

    int compute(int i, int j)
    {
        if (i == OUT_OF_BOUNDS) return j;
        if (j == OUT_OF_BOUNDS) return i;

        return compare(input[i], input[j]) ? i : j;
    }

    int build(int p, int l, int r) 
    {
        if (l != r) {
            int p1 = build(left(p), l, (l + r) / 2);
            int p2 = build(right(p), (l + r) / 2 + 1, r);

            return tree[p] = compute(p1, p2);
        } else {
            return tree[p] = l;
        }
    }

    int query(int p, int l, int r, int i, int j)
    {
        if (i > r || j < l) return OUT_OF_BOUNDS;
        if (l >= i && r <= j) return tree[p];

        int p1 = query(left(p), l, (l + r) / 2, i, j);
        int p2 = query(right(p), (l + r) / 2 + 1, r, i, j);

        return compute(p1, p2);
    }

    int update(int p, int l, int r, int i, int v)
    {
        if (i > r || i < l) return tree[p];
        if (i == l && i == r) return tree[p] = l;

        int p1 = update(left(p), l, (l + r) / 2, i, v);
        int p2 = update(right(p), (l + r) / 2 + 1, r, i, v);

        return tree[p] = compute(p1, p2);
    }
public:
    SegmentTree(const std::vector<int> input)
    {
        size = input.size();
        this->input = input;
        tree.assign(4 * size, 0);
        build(1, 0, size - 1);
    }

    int query(int i, int j)
    {
        return this->query(1, 0, size - 1, i, j);
    }

    int update(int i, int v)
    {
        this->input[i] = v;
        this->update(1, 0, size - 1, i, v);
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

void test_update_min()
{
    SegmentTree t = provide_tree();
    t.update(6, 0);
    if (t.query(0, 6) == 6) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_input_root()
{
    SegmentTree t = provide_tree();
    if (t.query(0, 6) == 5) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_input_left_branch()
{
    SegmentTree t = provide_tree();
    if (t.query(0, 3) == 2) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_input_right_branch()
{
    SegmentTree t = provide_tree();
    if (t.query(4, 6) == 5) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_input_intersection()
{
    SegmentTree t = provide_tree();
    if (t.query(3, 4) == 4) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_input_only_one_index()
{
    SegmentTree t = provide_tree();
    if (t.query(4, 4) == 4) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

int main()
{
    test_update_min();
    test_input_root();
    test_input_left_branch();
    test_input_right_branch();
    test_input_intersection();
    test_input_only_one_index();
}

#endif
