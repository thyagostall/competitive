#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    string word;
    int n;
    
    cin >> n;
    while (n--) {
        cin >> word;
        sort(begin(word), end(word));
        do {
            cout << word << endl;
        } while (next_permutation(begin(word), end(word)));
    }
}
