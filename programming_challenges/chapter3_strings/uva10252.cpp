#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

stack<char> to_stack(string str)
{
    stack<char> result;
    for (string::reverse_iterator it = str.rbegin(); it != str.rend(); it++) {
        result.push(*it);
    }
    return result;
}

int main()
{
    bool break_line = false;
    string first, second;

    while (!cin.eof()) {
        getline(cin, first);
        getline(cin, second);
        sort(first.begin(), first.end());
        sort(second.begin(), second.end());

        stack<char> a = to_stack(first);
        stack<char> b = to_stack(second);

        string result;
        while (!a.empty() && !b.empty()) {
            if (a.top() == b.top()) {
                result += a.top();
                a.pop();
                b.pop();
            } else if (a.top() < b.top()) {
                a.pop();
            } else {
                b.pop();
            }
        }

        if (break_line) cout << endl;
        cout << result;

        break_line = true;
    }
}
