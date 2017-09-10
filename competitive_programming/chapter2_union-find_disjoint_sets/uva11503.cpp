#include <iostream>
#include <map>
#include <vector>

class UnionFind 
{
    public:
        UnionFind(int size) 
        {
            parents.assign(size, 0);
            ranks.assign(size, 0);
            sizes.assign(size, 1);
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
                sizes[parent_j] += sizes[parent_i];
                if (ranks[parent_i] == ranks[parent_j]) 
                    ranks[parent_j]++;
            } else {
                parents[parent_j] = parent_i;
                sizes[parent_i] += sizes[parent_j];
            }
        }

        int size(int i)
        {
            return sizes[find_set(i)];
        }
    private:
        std::vector<int> parents, ranks, sizes;
};

using namespace std;

int main()
{
    int test_cases, relations;
    string person_a, person_b;

    cin >> test_cases;
    while (test_cases--) {
        cin >> relations;

        UnionFind network(relations + 1);
        map<string, int> people;
        int current = 0;
        while (relations--) {
            cin >> person_a >> person_b;

            if (people.find(person_a) == people.end()) people[person_a] = current++;
            if (people.find(person_b) == people.end()) people[person_b] = current++;

            network.union_set(people[person_a], people[person_b]);
            cout << network.size(people[person_a]) << endl;
        }
    }
}
