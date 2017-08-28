#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    int N, i, Y;
    string card, c;

    cin >> N;
    getline(cin, c);
    while (N--) {
        getline(cin, c);
        stringstream ss(c);

        Y = 0;
        for (i = 0; i < 52; i++) {
            ss >> card;
            cout << card << " ";
        }
        cout << endl;
    }
}
