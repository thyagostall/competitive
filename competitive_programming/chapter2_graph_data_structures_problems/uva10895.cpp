#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int m, n, line_size, buff;
    while (cin >> m >> n) {
        vector<vector<int>> indices(m, vector<int>());
        vector<vector<int>> values(m, vector<int>());

        for (int i = 0; i < m; i++) {
            cin >> line_size;
            for (int j = 0; j < line_size; j++) {
                cin >> buff;
                indices[i].push_back(buff);
            }
            for (int j = 0; j < line_size; j++) {
                cin >> buff;
                values[i].push_back(buff);
            }
        }

        vector<vector<int>> result_indices(n, vector<int>());
        vector<vector<int>> result_values(n, vector<int>());

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < indices[i].size(); j++) {
                result_indices[indices[i][j] - 1].push_back(i + 1);
                result_values[indices[i][j] - 1].push_back(values[i][j]);
            }
        }
        
        cout << n << " " << m << endl;
        for (int i = 0; i < n; i++) {
            line_size = result_indices[i].size();
            cout << line_size;
            for (int j = 0; j < line_size; j++) {
                cout << " " << result_indices[i][j];
            }
            cout << endl;
            for (int j = 0; j < line_size; j++) {
                if (j) cout << " ";
                cout << result_values[i][j];
            }
            cout << endl;
        }
    }
}
