#include <iostream>
#include <set>

#define MAX 102

using namespace std;

typedef enum {
    white = 0,
    black = 1
} Color;

typedef struct {
    int black_qty;
    set<int> black_nodes;
} Response;

set<int> graph[MAX];
bool visited[MAX];
Color color[MAX];
int node_qty;
int edge_qty;

void clear_graph();
void reset();
Response compute(int node, Response &best_response);
set<int> &connected_to(int node);
bool can_paint(int node);
Response get_current_candidate(const Response &best_response); 
int main()
{
    int graph_qty;
    int source, dest;


    cin >> graph_qty;
    while (graph_qty--) {
        cin >> node_qty >> edge_qty;
        
        clear_graph();
        for (int i = 0; i < edge_qty; i++) {
            cin >> source >> dest;
            graph[source].insert(dest);
            graph[dest].insert(source);
        }

        Response best_response { 0, {} };
        for (int node = 1; node <= node_qty; node++) {
            reset();
            best_response = compute(node, best_response);
        }

        cout << best_response.black_qty << endl;
        for (auto item : best_response.black_nodes) {
            if (item != *best_response.black_nodes.begin())
                cout << " ";
            cout << item;
        }
        cout << endl;
    }
}

void clear_graph()
{
    reset();
    for (int i = 0; i < MAX; i++) {
        graph[i].clear();
    }
}

void reset()
{
    for (int i = 0; i < MAX; i++) {
        visited[i] = false;
        color[i] = white;
    }
}

Response compute(int node, Response &best_response)
{
    if (node > node_qty)
        return get_current_candidate(best_response);

    if (visited[node])
        return best_response;
    visited[node] = true;

    if (can_paint(node)) {
        color[node] = black;
        best_response = compute(node + 1, best_response);
    }

    color[node] = white;
    best_response = compute(node + 1, best_response);
    visited[node] = false;
    return best_response;
}

set<int> &connected_to(int node)
{
    return graph[node];
}

bool can_paint(int node)
{
    bool valid = true;
    for (auto adj : connected_to(node))
        valid &= color[adj] != black;
    return valid;
}

Response get_current_candidate(const Response &current_best_response)
{
    Response new_best_response { 0, {} };

    for (int j = 1; j <= node_qty; j++) {
        if (color[j] != black) continue;
        
        new_best_response.black_qty++;
        new_best_response.black_nodes.insert(j);
    }

    return new_best_response.black_qty >= current_best_response.black_qty
        ? new_best_response
        : current_best_response;
}
