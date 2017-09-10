#include <iostream>
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

#include <sstream>

using namespace std;

int main()
{
    int test_cases, computer_quantity, computer_i, computer_j;
    string query, line;

    cin >> test_cases;
    while (test_cases--) {
        int success = 0, failure = 0;

        cin >> computer_quantity;
        getline(cin, line);

        UnionFind network(computer_quantity + 2);
        while (getline(cin, line) && line != "") {
            stringstream ss(line);
            ss >> query >> computer_i >> computer_j;

            if (query == "c") {
                network.union_set(computer_i, computer_j);
            } else {
                if (network.find_set(computer_i) == network.find_set(computer_j)) {
                    success++;
                } else {
                    failure++;
                }
            }
        }

        cout << success << "," << failure << endl;
        if (test_cases) cout << endl;
    }
}
