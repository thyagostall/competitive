#include <vector>
#include <limits>
#include <algorithm>

#include <iostream>

typedef enum 
{
    NONE, SET, RESET, TOGGLE
} PendingStatus;

class BinarySegmentTree
{
public:
    BinarySegmentTree(std::vector<bool> &input):
        size(input.size()),
        MAX_SIZE(4 * size)
    {
        this->current = 0;
        this->input = input;

        low.assign(MAX_SIZE, 0);
        high.assign(MAX_SIZE, 0);
        sumv.assign(MAX_SIZE, 0);
        pending.assign(MAX_SIZE, NONE);

        build(1, 0, size - 1);
    }

    void turn_on(int i, int j)
    {
        change_status(i, j, SET);
    }
    
    void turn_off(int i, int j)
    {
        change_status(i, j, RESET);
    }
    
    void toggle(int i, int j)
    {
        change_status(i, j, TOGGLE);
    }

    int query(int i, int j)
    {
        return this->query(1, i, j);
    }
private:
    std::vector<int> low, high, sumv;
    std::vector<PendingStatus> pending;
    std::vector<bool> input;
    int size, current;

    const int MAX_SIZE;
    
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

    PendingStatus get_status(PendingStatus old_status, PendingStatus new_status)
    {
        if (new_status == NONE)
            return old_status;

        if (new_status == SET || new_status == RESET || old_status == NONE) 
            return new_status;

        switch (old_status) {
            case NONE:
                return TOGGLE;
            case TOGGLE:
                return NONE;
            case SET: 
                return RESET;
            case RESET:
                return SET;
        }
    }

    void prop(int p)
    {
        if (left(p) < MAX_SIZE)
            pending[left(p)] = get_status(pending[left(p)], pending[p]);
        if (right(p) < MAX_SIZE)
            pending[right(p)] = get_status(pending[right(p)], pending[p]);
        pending[p] = NONE;
    }

    int calculate(int p)
    {
        PendingStatus status = pending[p];
        prop(p);
        switch (status) {
            case NONE: 
                return sumv[p];
            case SET: 
                return sumv[p] = high[p] - low[p] + 1;
            case RESET: 
                return sumv[p] = 0;
            case TOGGLE: 
                return sumv[p] = high[p] - low[p] + 1 - sumv[p];
        }
    }

    void update(int p)
    {
        sumv[p] = calculate(left(p)) + calculate(right(p));
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

    void change_status(int i, int j, PendingStatus status)
    {
        this->change_status(1, i, j, status);
    }

    void change_status(int p, int i, int j, PendingStatus status)
    {
        if (j < low[p] || i > high[p])
            return;

        if (i <= low[p] && j >= high[p]) {
            pending[p] = get_status(pending[p], status);
            return;
        }
        
        prop(p);

        change_status(left(p), i, j, status);
        change_status(right(p), i, j, status);

        update(p);
    }

    int query(int p, int i, int j)
    {
        if (j < low[p] || i > high[p])
            return 0;

        if (i <= low[p] && j >= high[p])
            return calculate(p);
        
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

void assert_true(bool condition) 
{
    if (condition) {
        cout << "✔ Test - Passed" << endl;
    } else {
        cout << "✗ Test - Failed" << endl;
    }
}

BinarySegmentTree provide_tree()
{
    bool arr[] = {false, false, false, false, false, false, false};
    vector<bool> input(arr, arr + 7);
    return BinarySegmentTree(input);
}

void test_all_bits_turned_off()
{
    BinarySegmentTree p = provide_tree();
    int result = p.query(0, 6);
    assert_true(result == 0);
}

void test_turn_off_all_bits()
{
    BinarySegmentTree p = provide_tree();
    p.turn_off(0, 6);
    int result = p.query(0, 6);
    assert_true(result == 0);
}

void test_turn_off_left_branch()
{
    BinarySegmentTree p = provide_tree();
    p.turn_on(0, 6);
    p.turn_off(0, 3);
    int result = p.query(0, 6);
    assert_true(result == 3);
}

void test_turn_off_right_branch()
{
    BinarySegmentTree p = provide_tree();
    p.turn_on(0, 6);
    p.turn_off(4, 6);
    int result = p.query(0, 6);
    assert_true(result == 4);
}

void test_turn_off_overlaping_interval()
{
    BinarySegmentTree p = provide_tree();
    p.turn_on(0, 6);
    p.turn_off(3, 4);
    int result = p.query(0, 6);
    assert_true(result == 5);
}

void test_turn_off_a_single_node()
{
    BinarySegmentTree p = provide_tree();
    p.turn_on(0, 6);
    p.turn_off(4, 4);
    int result = p.query(0, 6);
    assert_true(result == 6);
}

void test_toggle_all_bits()
{
    BinarySegmentTree p = provide_tree();
    p.toggle(0, 6);
    int result = p.query(0, 6);
    assert_true(result == 7);
}

void test_toggle_left_branch()
{
    BinarySegmentTree p = provide_tree();
    p.turn_on(0, 6);
    p.toggle(0, 3);
    int result = p.query(0, 6);
    assert_true(result == 3);
}

void test_toggle_right_branch()
{
    BinarySegmentTree p = provide_tree();
    p.turn_on(0, 6);
    p.toggle(4, 6);
    int result = p.query(0, 6);
    assert_true(result == 4);
}

void test_toggle_overlaping_interval()
{
    BinarySegmentTree p = provide_tree();
    p.toggle(3, 4);
    int result = p.query(0, 6);
    assert_true(result == 2);
}

void test_toggle_a_single_node()
{
    BinarySegmentTree p = provide_tree();
    p.toggle(4, 4);
    int result = p.query(0, 6);
    assert_true(result == 1);
}

void test_turn_on_all_bits()
{
    BinarySegmentTree p = provide_tree();
    p.turn_on(0, 6);
    int result = p.query(0, 6);
    assert_true(result == 7);
}

void test_turn_on_left_branch()
{
    BinarySegmentTree p = provide_tree();
    p.turn_on(0, 3);
    int result = p.query(0, 6);
    assert_true(result == 4);
}

void test_turn_on_right_branch()
{
    BinarySegmentTree p = provide_tree();
    p.turn_on(4, 6);
    int result = p.query(0, 6);
    assert_true(result == 3);
}

void test_turn_on_overlaping_interval()
{
    BinarySegmentTree p = provide_tree();
    p.turn_on(3, 4);
    int result = p.query(0, 6);
    assert_true(result == 2);
}

void test_turn_on_a_single_node()
{
    BinarySegmentTree p = provide_tree();
    p.turn_on(4, 4);
    int result = p.query(0, 6);
    assert_true(result == 1);
}

int main()
{
    test_all_bits_turned_off();
    
    test_toggle_all_bits();
    test_toggle_left_branch();
    test_toggle_right_branch();
    test_toggle_overlaping_interval();
    test_toggle_a_single_node();
    
    test_turn_on_all_bits();
    test_turn_on_left_branch();
    test_turn_on_right_branch();
    test_turn_on_overlaping_interval();
    test_turn_on_a_single_node();

    test_turn_off_all_bits();
    test_turn_off_left_branch();
    test_turn_off_right_branch();
    test_turn_off_overlaping_interval();
    test_turn_off_a_single_node();
}

#endif
