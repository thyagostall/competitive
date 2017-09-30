#include <vector>
#include <limits>
#include <algorithm>

class SumSegmentTree
{
public:
    SumSegmentTree(std::vector<int> &input):
        size(input.size())
    {
        this->current = 0;
        this->input = input;

        low.assign(4 * size, 0);
        high.assign(4 * size, 0);
        sumv.assign(4 * size, 0);
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
    std::vector<int> low, high, sumv, delta, input;
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
        sumv[p] = sumv[left(p)] + delta[left(p)] + sumv[right(p)] + delta[right(p)];
    }

    void build(int p, int l, int r)
    {
        low[p] = l;
        high[p] = r;

        if (l == r) {
            sumv[p] = input[current++];
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
            delta[p] += val * (high[p] - low[p] + 1);
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
            return 0;

        if (i <= low[p] && j >= high[p])
            return sumv[p] + delta[p];

        prop(p);

        int sum_left = query(left(p), i, j);
        int sum_right = query(right(p), i, j);

        update(p);

        return sum_left + sum_right;
    }
};

#ifndef TESTS
#define TESTS

#include <iostream>

using namespace std;

SumSegmentTree provide_tree()
{
    int arr[] = {5, 10, 15, 20, 25, 30, 35};
    vector<int> input(arr, arr + 7);
    return SumSegmentTree(input);
}

void test_increment_everything()
{
    SumSegmentTree t = provide_tree();
    t.increment(0, 6, 10);
    if (t.query(0, 6) == 210) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_increment_left_branch()
{
    SumSegmentTree t = provide_tree();
    t.increment(0, 3, 10);
    if (t.query(0, 3) == 90) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }

    if (t.query(0, 6) == 180) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_increment_right_branch()
{
    SumSegmentTree t = provide_tree();
    t.increment(4, 6, 10);
    if (t.query(4, 6) == 120) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }

    if (t.query(0, 6) == 170) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_increment_intersection()
{
    SumSegmentTree t = provide_tree();
    t.increment(3, 4, 10);
    if (t.query(3, 4) == 65) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }

    if (t.query(0, 6) == 160) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_increment_only_one_index()
{
    SumSegmentTree t = provide_tree();
    t.increment(4, 4, 10);
    if (t.query(4, 4) == 35) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }

    if (t.query(0, 6) == 150) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_input_root()
{
    SumSegmentTree t = provide_tree();
    if (t.query(0, 6) == 140) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_input_left_branch()
{
    SumSegmentTree t = provide_tree();
    if (t.query(0, 3) == 50) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_input_right_branch()
{
    SumSegmentTree t = provide_tree();
    if (t.query(4, 6) == 90) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_input_intersection()
{
    SumSegmentTree t = provide_tree();
    if (t.query(3, 4) == 45) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

void test_input_only_one_index()
{
    SumSegmentTree t = provide_tree();
    if (t.query(4, 4) == 25) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

int main()
{
    test_increment_everything();
    test_increment_left_branch();
    test_increment_right_branch();
    test_increment_intersection();
    test_increment_only_one_index();

    test_input_root();
    test_input_left_branch();
    test_input_right_branch();
    test_input_intersection();
    test_input_only_one_index();
}

#endif
