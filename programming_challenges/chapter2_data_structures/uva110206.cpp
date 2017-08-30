#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

#define INFINITY 999999
#define ERDOS_NAME "Erdos, P."

using namespace std;

void split_line(vector<string> &result, string line) {
    int ant;

    ant = 0;
        
    for (int i = 1; i < line.size(); i++) {
        if (line[i - 1] == '.' && (line[i] == ',' || line[i] == ':') || line[i] == ':') {
            result.push_back(line.substr(ant, i - ant));
            ant = i + 1;

            while (isspace(line[ant]))
                ant++;

            if (line[i] == ':')
                break;
        }
    }
}

int main() {
    vector<vector<string> > lines;
    vector<bool> visited;

    int scenario_qty, scenario = 1;

    cin >> scenario_qty;
    while (scenario_qty-- > 0) {
        int current = 0, paper_qty, author_qty;
        map<string, int> erdos_numbers;
        vector<string> read_names;
        string line;

        visited.clear();
        lines.clear();

        cin >> paper_qty;
        cin >> author_qty;

        getline(cin, line);

        if (cin.eof())
            break;

        for (int i = 0; i < paper_qty; i++) {
            vector<string> names;

            getline(cin, line);
            split_line(names, line);
            lines.push_back(names);
            visited.push_back(false);

            for (int j = 0; j < names.size(); j++) {
                erdos_numbers[names[j]] = INFINITY;
                read_names.push_back(names[j]);
            }
        }

        queue<string> to_visit;
        erdos_numbers[ERDOS_NAME] = 0;

        to_visit.push(ERDOS_NAME);
        while (!to_visit.empty()) {
            string current_name = to_visit.front();
            to_visit.pop();

            for (int i = 0; i < lines.size(); i++) {
                if (visited[i] || find(lines[i].begin(), lines[i].end(), current_name) == lines[i].end())
                    continue;

                for (int j = 0; j < lines[i].size(); j++) {
                    if (lines[i][j] == current_name)
                        continue;

                    if (erdos_numbers[lines[i][j]] > erdos_numbers[current_name] + 1) {
                        erdos_numbers[lines[i][j]] = erdos_numbers[current_name] + 1;
                        to_visit.push(lines[i][j]);
                    }
                }

                visited[i] = true;
            }
        }

        erdos_numbers[ERDOS_NAME] = 0;

        if (find(read_names.begin(), read_names.end(), ERDOS_NAME) == read_names.end())
            read_names.push_back(ERDOS_NAME);
        
        cout << "Scenario " << scenario++ << endl;
        for (int i = 0; i < author_qty; i++) {
            getline(cin, line);

            if (erdos_numbers[line] < INFINITY && find(read_names.begin(), read_names.end(), line) != read_names.end())
                cout << line << " " << erdos_numbers[line] << endl;
            else
                cout << line << " infinity" << endl;
        }
    }

    return EXIT_SUCCESS;
}
