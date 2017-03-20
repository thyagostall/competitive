#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#define MAX_STR 1000

using namespace std;

bool is_space(char c)
{
    return c == ' ';
}

string hash_anagram(string in)
{
    string result;
    for (auto c : in) {
        if (is_space(c)) {
            continue;
        }
        result += c;
    }
    sort(begin(result), end(result));
    return result;
}

int main()
{
    int n, i, j;
    string phrase = "-";
    vector<string> phrases;

    cin >> n;
    cin.ignore(MAX_STR, '\n');
    cin.ignore(MAX_STR, '\n');
    while (n--) {
        phrases.clear();
        while (getline(cin, phrase) && phrase != "") {
            phrases.push_back(phrase);
        }

        sort(begin(phrases), end(phrases));
        for (i = 0; i < phrases.size(); i++) {
            for (j = i + 1; j < phrases.size(); j++) {
                if (hash_anagram(phrases[i]) == hash_anagram(phrases[j])) {
                    cout << phrases[i] << " = " << phrases[j] << endl;
                }
            }
        }
        if (n) {
            cout << endl;
        }
    }
}
