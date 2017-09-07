#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>

using namespace std;

void printv(string &str)
{
    for (int i = 0; i < str.length(); i++) {
        if (i) printf(" ");
        printf("%c", str[i]);
    }
    printf("\n");
}

bool string_starts_with(string a, string b)
{
    if (b.length() > a.length()) return false;

    for (int i = 0; i < b.length(); i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

void simulate(stack<char> stack, string input, string &goal, string output, string seq)
{
    if (!string_starts_with(goal, output)) {
        return;
    } else if (goal == output) {
        printv(seq);
    }

    if (input != "") {
        stack.push(input[0]);
        simulate(stack, input.substr(1), goal, output, seq + "i");
        stack.pop();
    }

    if (!stack.empty()) {
        output = output + stack.top();
        stack.pop();
        simulate(stack, input, goal, output, seq + "o");
    }
}

int main()
{
    char buffer[100];

    while (!feof(stdin)) { 
        vector<char> str;

        scanf("%s\n", buffer);
        string input {buffer};
        scanf("%s\n", buffer);
        string goal {buffer};

        printf("[\n");        
        simulate(stack<char>(), input, goal, "", "");
        printf("]\n");        
    }
}
