#include <iostream>
#include <sstream>

using namespace std;

const int SPADES = 0;
const int HEARTS = 1;
const int DIAMONDS = 2;
const int CLUBS = 3;

int si(char suit) {
    switch (suit) {
        case 'S': return SPADES;
        case 'H': return HEARTS;
        case 'D': return DIAMONDS;
        case 'C': return CLUBS;
    }
}

char sn(int index) {
    switch (index) {
        case SPADES: return 'S';
        case HEARTS: return 'H';
        case DIAMONDS: return 'D';
        case CLUBS: return 'C';
    }
}

int main()
{
    bool Ss[4];
    int P, i, Sc[4], s, m, b;
    string game, card[13];

    while (getline(cin, game)) {
        istringstream iss(game);
        P = 0;
        for (i = 0; i < 4; Sc[i] = 0, Ss[i] = false, i++);

        // Rule 1
        for (i = 0; i < 13; i++) {
            iss >> card[i];
            switch (card[i][0]) {
                case 'A': P += 4; break;
                case 'K': P += 3; break;
                case 'Q': P += 2; break;
                case 'J': P += 1; break;
            }
            
            Sc[si(card[i][1])]++;
        }

        // Rule 2, 3, and 4
        for (i = 0; i < 13; i++) {
            s = si(card[i][1]);
            switch (card[i][0]) {
                case 'K':
                    if (Sc[s] - 1 == 0) P--;
                    break;
                case 'Q': 
                    if (Sc[s] - 1 <= 1) P--;
                    break;
                case 'J': 
                    if (Sc[s] - 1 <= 2) P--;
                    break;
            }
        }

        // Stopped
        for (i = 0; i < 13; i++) {
            s = si(card[i][1]);
            switch (card[i][0]) {
                case 'A':
                    Ss[s] = true;
                    break;
                case 'K':
                    Ss[s] = Ss[s] || Sc[s] > 1;
                    break;
                case 'Q':
                    Ss[s] = Ss[s] || Sc[s] > 2;
            }
        }

        // No trump (needs to ignore rules 5, 6, 7)
        if (P >= 16 && Ss[0] && Ss[1] && Ss[2] && Ss[3]) {
            cout << "BID NO-TRUMP" << endl;
            continue;
        }

        // Rules 5, 6, 7
        for (i = 0; i < 4; i++) {
            switch (Sc[i]) {
                case 0: P += 2; break;
                case 1: P += 2; break;
                case 2: P += 1; break;
            }
        }

        if (P >= 14) {
            m = 0, b = -1;
            for (i = 0; i < 4; i++) {
                m = Sc[i] > m ? Sc[i] : m;
            }

            for (i = 0; i < 4; i++) {
                if (Sc[i] == m) {
                    break;
                }
            }

            cout << "BID " << sn(i) << endl;
        } else {
            cout << "PASS" << endl;
        }
    }
}
