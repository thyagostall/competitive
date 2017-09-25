#include <vector>
#include <limits>
#include <algorithm>

class SegmentTree
{
public:
    SegmentTree(std::vector<int> &input):
        size(input.size())
    {
        this->current = 0;
        this->input = input;

        low.assign(4 * size, 0);
        high.assign(4 * size, 0);
        minv.assign(4 * size, 0);
        delta.assign(4 * size, 0);

        build(1, 0, size - 1);
    }

    void increment(int i, int j, int val)
    {
        this->increment(1, i, j, val);
    }

    int query(int i, int j)
    {
        return this->query(1, i, j);
    }
private:
    std::vector<int> low, high, minv, delta, input;
    int size, current;

    int left(int p)
    {
        return p << 1;
    }

    int right(int p)
    {
        return (p << 1) + 1;
    }

    int half(int l, int r)
    {
        return (l + r) / 2;
    }

    void prop(int p)
    {
        delta[left(p)] += delta[p];
        delta[right(p)] += delta[p];
        delta[p] = 0;
    }

    void update(int p)
    {
        minv[p] = std::min(minv[left(p)] + delta[left(p)], minv[right(p)] + delta[right(p)]);
    }

    void build(int p, int l, int r)
    {
        low[p] = l;
        high[p] = r;

        if (l == r) {
            minv[p] = input[current++];
            return;
        }

        int h = half(l, r);
        build(left(p), l, h);
        build(right(p), h + 1, r);

        update(p);
    }

    void increment(int p, int i, int j, int val)
    {
        if (j < low[p] || i > high[p])
            return;

        if (i <= low[p] && j >= high[p]) {
            delta[p] += val;
            return;
        }

        prop(p);

        increment(left(p), i, j, val);
        increment(right(p), i, j, val);

        update(p);
    }

    int query(int p, int i, int j)
    {
        if (j < low[p] || i > high[p])
            return std::numeric_limits<int>::max();

        if (i <= low[p] && j >= high[p])
            return minv[p] + delta[p];

        prop(p);

        int min_left = query(left(p), i, j);
        int min_right = query(right(p), i, j);

        update(p);

        return std::min(min_left, min_right);
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

void test_input_root()
{
    SegmentTree t = provide_tree();
    if (t.query(0, 6) == 11) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_input_left_branch()
{
    SegmentTree t = provide_tree();
    if (t.query(0, 3) == 13) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_input_right_branch()
{
    SegmentTree t = provide_tree();
    if (t.query(4, 6) == 11) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_input_intersection()
{
    SegmentTree t = provide_tree();
    if (t.query(3, 4) == 15) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_input_only_one_index()
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
    test_input_root();
    test_input_left_branch();
    test_input_right_branch();
    test_input_intersection();
    test_input_only_one_index();
}

#endif
