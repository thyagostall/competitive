#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

string to_string(vector<int> &expression)
{
    string result = "";
    for (int i = 0; i < expression.size(); i++) {
        if (i) result += "+";
        result += to_string(expression[i]);
    }
    return result;
}

int sum(vector<int> &expression)
{
    int result = 0;
    for (auto &t: expression)
        result += t;
    return result;
}

void print_expressions(vector<string> expressions)
{
    for (auto &expression: expressions) {
        cout << expression << endl;
    }
}

void search(int goal, int current_term, vector<int> &terms, vector<int> &current_expression, vector<string> &result)
{
    int current_sum = sum(current_expression);
    if (current_sum > goal) {
        return;
    } else if (current_sum == goal) {
        result.push_back(to_string(current_expression));
    }

    for (int i = current_term; i < terms.size(); i++) {
        current_expression.push_back(terms[i]);
        search(goal, i + 1, terms, current_expression, result);
        current_expression.pop_back();
    }
}

void remove_duplicates(vector<string> &value, vector<string> &result)
{
    for (int i = 0; i < value.size(); i++) {
        if (find(result.begin(), result.end(), value[i]) == result.end())
            result.push_back(value[i]);
    }
}

void search(int goal, vector<int> &terms, vector<string> &result)
{
    vector<int> current;
    vector<string> temp_result;
    search(goal, 0, terms, current, temp_result);
    remove_duplicates(temp_result, result);
}

int main()
{
    int goal, list_size;
    while (cin >> goal >> list_size && goal && list_size) {
        vector<int> terms(list_size);
        for (int i = 0; i < list_size; i++)
            cin >> terms[i];

        vector<string> result;
        search(goal, terms, result);
    
        cout << "Sums of " << goal << ":" << endl; 
        if (result.size()) {
            print_expressions(result);
        } else {
            cout << "NONE" << endl;
        }
    }
}
