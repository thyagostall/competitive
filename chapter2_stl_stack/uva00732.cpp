#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>

using namespace std;

void printv(vector<char> &str)
{
    for (int i = 0; i < str.size(); i++) {
        if (i) printf(" ");
        printf("%c", str[i]);
    }
    printf("\n");
}

void simulate(vector<char> &operations, string &input, string &goal)
{
    stack<char> auxiliary;
    string result;
    int current = 0;
    
    for (auto &operation : operations) {
        if (operation == 'i') {
            auxiliary.push(input[current++]);
        } else if (operation == 'o') {
            if (auxiliary.empty()) break;
            result.push_back(auxiliary.top());
            auxiliary.pop();
        }
    }

    if (result == goal) {
        printv(operations);
    }    
}

bool is_anagram(string first, string second)
{
    sort(first.begin(), first.end());
    sort(second.begin(), second.end());
    return first == second;
}

void generate_permutation(vector<char> input, int i, int is, int os, string& word, string& goal)
{
    if (os > is ||
        os > word.size() ||
        is > word.size()) {
        return;
    }

    if (i == word.size() * 2) {
        simulate(input, word, goal);
        return;
    } 

    input.push_back('i');
    generate_permutation(input, i + 1, is + 1, os, word, goal);
    input.pop_back();
    input.push_back('o');
    generate_permutation(input, i + 1, is, os + 1, word, goal);
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
        generate_permutation(str, 0, 0, 0, input, goal);
        printf("]\n");        
    }
}
