#include <iostream>
#include <string>
#include <sstream>

#define DECK_SIZE 52

using namespace std;

string *get_extended_card(int i) {
    string *result = new string;
    int value;
    char suit;
    
    if (i < 13) 
        suit = 'C';
    else if (i < 26)
        suit = 'D';
    else if (i < 39)
        suit = 'H';
    else
        suit = 'S';

    value = i % 13;

    switch (value) {
        case 12:
            *result = "Ace";
            break;
        case 11:
            *result = "King";
            break;
        case 10:
            *result = "Queen";
            break;
        case 9:
            *result = "Jack";
            break;
        default:
            ostringstream convert;
            convert << value + 2;
            *result = convert.str();
    }

    *result += " of ";

    switch (suit) {
        case 'C':
            *result += "Clubs";
            break;
        case 'D':
            *result += "Diamonds";
            break;
        case 'H':
            *result += "Hearts";
            break;
        case 'S':
            *result += "Spades";
            break;
    }

    return result;
}

void shuffle(int shuffle_order[DECK_SIZE], int deck[DECK_SIZE]) {
    int result[DECK_SIZE];

    for (int i = 0; i < DECK_SIZE; i++) {
        result[i] = deck[shuffle_order[i] - 1];
    }
    
    for (int i = 0; i < DECK_SIZE; i++) {
        deck[i] = result[i];
    }
}

int main() {
    int known_dealer[100][DECK_SIZE], deck[DECK_SIZE];
    int known_shuffle, test_case_qty, shuffle_num;
    string line;

    cin >> test_case_qty;
    while (test_case_qty-- > 0) {
        cin >> known_shuffle;

        for (int i = 0; i < known_shuffle; i++) {
            for (int j = 0; j < DECK_SIZE; j++) {
                cin >> known_dealer[i][j];
            }
        }

        for (int i = 0; i < DECK_SIZE; i++) {
            deck[i] = i;
        }

        getline(cin, line);
        
        while (getline(cin, line) && line.length() > 0) {
            istringstream buffer(line);
            buffer >> shuffle_num;         

            shuffle(known_dealer[shuffle_num - 1], deck);
        }
        
        for (int i = 0; i < DECK_SIZE; i++) {
            cout << *get_extended_card(deck[i]) << endl;
        }

        if (test_case_qty)
            cout << endl;
    }
}
