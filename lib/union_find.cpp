#include <vector>

class UnionFind 
{
    public:
        UnionFind(int size) 
        {
            parents.assign(size, 0);
            ranks.assign(size, 0);
            for (int i = 0; i < size; i++) parents[i] = i;
        }

        int find_set(int i) 
        {
            return parents[i] == i ? i : parents[i] = find_set(parents[i]);
        }

        bool same_set(int i, int j)
        {
            return find_set(i) == find_set(j);
        }

        void union_set(int i, int j)
        {
            if (same_set(i, j)) return;

            int parent_i = find_set(i);
            int parent_j = find_set(j);
            if (ranks[parent_i] <= parents[parent_j]) {
                parents[parent_i] = parent_j;
                if (ranks[parent_i] == ranks[parent_j]) 
                    ranks[parent_j]++;
            } else {
                parents[parent_j] = parent_i;
            }
        }
    private:
        std::vector<int> parents, ranks;
};

#ifndef TESTS
#define TESTS

#include <iostream>

using namespace std;

void test_create_union_find()
{
    UnionFind u(5);
    cout << "✔ Test - Passed" << endl;
}

void test_find_set_they_must_be_themselves()
{
    UnionFind u(2);
    if (u.find_set(0) != 0) {
        cout << "✗ Test - Failed [find_set(0) must be 0]" << endl;
    }
    if (u.find_set(1) != 1) {
        cout << "✗ Test - Failed [find_set(1) must be 1]" << endl;
    }
    cout << "✔ Test - Passed" << endl;
}

void test_union_set_they_must_be_the_same()
{
    UnionFind u(2);
    u.union_set(0, 1);
    if (u.find_set(0) != u.find_set(1)) {
        cout << "✗ Test - Failed [find_set(0) must be 0]" << endl;
        cout << "✗ Test - Failed [find_set(1) must be 0]" << endl;
    }
    cout << "✔ Test - Passed" << endl;
}

int main()
{
    test_create_union_find();
    test_find_set_they_must_be_themselves();
    test_union_set_they_must_be_the_same();
}

#endif
