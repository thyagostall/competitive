#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

int main()
{
    string raw_word, raw_guesses;
    int round, errors;

    while (cin >> round && round >= 0) {
        cin >> raw_word;
        cin >> raw_guesses;
        cout << "Round " << round << endl;

        errors = 0;

        unordered_set<char> guesses;
        unordered_set<char> word{begin(raw_word), end(raw_word)};
        unordered_set<char> correct;
        for (auto g : raw_guesses) {
            if (guesses.find(g) != word.end()) continue;
            guesses.insert(g);

            if (word.find(g) != word.end()) {
                correct.insert(g);
            } else {
                errors++;
            }

            if (correct == word) {
                cout << "You win." << endl;
                break;
            } else if (errors >= 7) {
                cout << "You lose." << endl;
                break;
            }
        }

        if (correct != word && errors < 7) {
            cout << "You chickened out." << endl;
        }
    }
}
