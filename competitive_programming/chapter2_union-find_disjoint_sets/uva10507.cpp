#include <iostream>
#include <set>
#include <map>

#include <vector>

class UnionFind 
{
    public:
        UnionFind(int size) 
        {
            set_count = size;
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

            set_count--;
        }

        int count()
        {
            return set_count;
        }
    private:
        std::vector<int> parents, ranks;
        int set_count;
};

using namespace std;

bool will_wake(int i, bool *brain_conn, int count, UnionFind &brain, int awake)
{
    int connected = 0;
    for (int x = 1; x <= count; x++) {
        if (brain_conn[x] && brain.same_set(x, awake)) connected++;
    }
    return connected >= 3;
}

int main()
{
    int count, connections;
    string buff;
    while (cin >> count) {
        bool brain_conn[count + 1][count + 1];
        for (int i = 1; i <= count; i++) {
            for (int j = 1; j <= count; j++) {
                brain_conn[i][j] = false;
            }
        }

        int current = 1;
        UnionFind brain(count + 1);
        map<char, int> convert;
        
        cin >> connections;
        cin >> buff;

        convert[buff[0]] = current++;
        convert[buff[1]] = current++;
        convert[buff[2]] = current++;

        brain.union_set(0, 1);
        brain.union_set(1, 2);
        brain.union_set(1, 3);

        brain_conn[1][2] = true;
        brain_conn[1][3] = true;
        brain_conn[2][1] = true;
        brain_conn[3][1] = true;

        int awake = brain.find_set(1);
        
        while (connections--) {
            cin >> buff;
            char x = buff[0], y = buff[1];
            if (!convert[x]) convert[x] = current++;
            if (!convert[y]) convert[y] = current++;

            brain_conn[convert[x]][convert[y]] = true;
            brain_conn[convert[y]][convert[x]] = true;
        }

        int years = 0;
        while (brain.count() > 1) {
            set<int> next_awake;
            for (int i = 1; i <= count; i++) {
                if (brain.same_set(awake, i)) continue;
                
                if (will_wake(i, brain_conn[i], count, brain, awake)) {
                    next_awake.insert(i);
                }
            }
            years++;
            if (!next_awake.size()) {
                years = -1;
                break;
            }
            for (auto &i : next_awake) brain.union_set(awake, i);
        }

        if (years < 0) {
            cout << "THIS BRAIN NEVER WAKES UP" << endl;
        } else {
            cout << "WAKE UP IN, " << years << ", YEARS" << endl;
        }
    }
}
