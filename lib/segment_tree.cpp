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

    bool compare(int a, int b) 
    {
        return a <= b;
    }

    void build(int p, int l, int r) 
    {
        if (l != r) {
            build(left(p), l, (l + r) / 2);
            build(right(p), (l + r) / 2 + 1, r);

            int p1 = tree[left(p)];
            int p2 = tree[right(p)];

            tree[p] = compare(input[p1], input[p2]) ? p1 : p2;
        } else {
            tree[p] = l;
        }
    }

    int query(int p, int l, int r, int i, int j)
    {
        if (i > r || j < l) return -1;
        if (l >= i && r <= j) return tree[p];

        int p1 = query(left(p), l, (l + r) / 2, i, j);
        int p2 = query(right(p), (l + r) / 2 + 1, r, i, j);

        if (p1 == -1) return p2;
        if (p2 == -1) return p1;

        return compare(input[p1], input[p2]) ? p1 : p2;
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
};

#ifndef TESTS
#define TESTS

#include <iostream>

using namespace std;

void test_with_simple_example()
{
    int arr[] = {18, 17, 13, 19, 15, 11, 20};
    vector<int> input(arr, arr + 7);

    SegmentTree t(input);
    cout << "query(1, 3)=" << t.query(1, 3) << endl;
    cout << "query(4, 6)=" << t.query(4, 6) << endl;
}

int main()
{
    test_with_simple_example();
}

#endif
