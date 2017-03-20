#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define MAX_WORD_SIZE 25

using namespace std;

string hash_anagram(string word)
{
    transform(begin(word), end(word), begin(word), ::tolower);
    sort(begin(word), end(word));
    return word;
}

int main()
{
    string word, hashed;
    vector<string> words;
    unordered_map<string, int> hash_count;

    while (cin >> word && word != "#") {
        words.push_back(word);
        hashed = hash_anagram(word);
        hash_count[hashed]++;
    }

    sort(begin(words), end(words));
    for (auto word : words) {
        hashed = hash_anagram(word);
        if (hash_count[hashed] == 1) {
            cout << word << endl;
        }
    }
}
