#include <iostream>

#define MAX 30

using namespace std;

void clear_connections(bool *a)
{
    for (int i = 0; i < MAX; i++) a[i] = false;
}

int to_index(char a)
{
    return a - 'A';
}

int main()
{
    string edge, vertices;
    int test_cases;
    bool has_connection[MAX];

    cin >> test_cases;
    while (test_cases--) {
        clear_connections(has_connection);
        
        int edge_count = 0;
        while (cin >> edge && edge[0] != '*') {
            edge_count++;
            has_connection[to_index(edge[1])] = true;
            has_connection[to_index(edge[3])] = true;
        }

        cin >> vertices;
        int vertice_count = 0, acorn_count = 0;
        for (auto &v : vertices) {
            if (v == ',') continue;
            vertice_count++;
            if (!has_connection[to_index(v)]) {
                acorn_count++;
            }
        }
        int components = vertice_count - edge_count;
        cout << "There are " << components - acorn_count << " tree(s) and ";
        cout << acorn_count << " acorn(s)." << endl;
    }
}
