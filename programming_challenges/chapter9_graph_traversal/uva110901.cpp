#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    int n, l, i, j;

    while (cin >> n && n)
    {
        cin >> l;
        vector< vector<bool> > graph(n, vector<bool>(n, false));

        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                graph[i][j] = false;

        while (l--)
        {
            cin >> i >> j;
            graph[j][i] = graph[i][j] = true;
        }

        queue<int> fifo;
        vector<int> level(n, ~0);

        fifo.push(0);
        level[0] = 0;             
        while (!fifo.empty())
        {
            int curr = fifo.front();
            fifo.pop();

            for (int i = 0; i < n; i++)
            {
                if (graph[curr][i])
                {
                    if (level[i] == ~0)
                    {
                        level[i] = level[curr] + 1;
                        fifo.push(i);
                    }
                    else if (level[i] % 2 == level[curr] % 2)
                    {
                        while (!fifo.empty()) fifo.pop();
                        break;
                    }
                }
            }
        }

        bool bicolorable = true;
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (level[i] == level[j] && graph[i][j])
                {
                    bicolorable = false;
                    break;
                }

        if (bicolorable)
            cout << "BICOLORABLE." << endl;
        else
            cout << "NOT BICOLORABLE." << endl;
    }

    return 0;
}
