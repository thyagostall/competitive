#include <iostream>

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

using namespace std;

int main()
{
    int test_cases, lines, times, queries, a, b, query_num;
    char query;
    string buff_str;

    cin >> test_cases;
    for (int t = 1; t <= test_cases; t++) {
        cin >> lines;
        vector<bool> values;
        while (lines--) {
            cin >> times;
            cin >> buff_str;

            while (times--) {
                for (const auto &c : buff_str) {
                    values.push_back(c == '1');
                }
            }
        }

        BinarySegmentTree bst(values);
        cout << "Case " << t << ":" << endl;

        cin >> queries;
        query_num = 0;
        while (queries--) {
            cin >> query >> a >> b;

            if (query == 'F') {
                bst.turn_on(a, b);
            } else if (query == 'E') {
                bst.turn_off(a, b);
            } else if (query == 'I') {
                bst.toggle(a, b);
            } else {
                cout << "Q" << ++query_num << ": " << bst.query(a, b) << endl;
            }
        }
    }
}
