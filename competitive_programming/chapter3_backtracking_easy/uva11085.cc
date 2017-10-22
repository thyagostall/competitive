#include <iostream>
#include <vector>
#include <limits>

#define MAX 8

using namespace std;

bool is_valid(vector<int> &config)
{
    for (int i = 0; i < config.size(); i++) {        
        for (int j = 0; j < config.size(); j++) {
            if (i == j) continue;
            if (config[i] == config[j] || abs(config[i] - config[j]) == abs(i - j)) return false;
        }
    }
    return true;
}

int compute(vector<int> &config, vector<int> &initial)
{
    int result = 0;
    for (int i = 0; i < MAX; i++) {
        result += config[i] != initial[i];
    }
    return result;
}

int backtrack(vector<int> &config, vector<int> &initial)
{
    if (!is_valid(config)) 
        return numeric_limits<int>::max();

    if (config.size() == MAX)
        return compute(config, initial);

    int result = numeric_limits<int>::max();
    for (int i = 0; i < MAX; i++) {
        config.push_back(i);
        result = min(result, backtrack(config, initial));
        config.pop_back();
    }
    return result;
}

int main()
{
    vector<int> game(MAX), current_config;
    int case_number = 1; 
    while (cin >> game[0]) {
        game[0] = game[0] - 1;
        for (int i = 1; i < MAX; i++) {
            cin >> game[i];
            game[i] = game[i] - 1;
        }

        cout << "Case " << case_number++ << ": "
             << backtrack(current_config, game)
             << endl; 
    }
}
