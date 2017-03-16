#include <iostream>
#include <algorithm>

using namespace std;

char to_lower(char c)
{
    if (c < 'A' || c > 'Z') {
        return c;
    }

    return c - 'A' + 'a';
}

bool is_first_smaller(char a, char b)
{
    char la = to_lower(a);
    char lb = to_lower(b);
    if (la == lb) {
        return a < b;
    }

    return la < lb; 
}

int main()
{
    string word;
    int n;
    
    cin >> n;
    while (n--) {
        cin >> word;
        sort(begin(word), end(word), is_first_smaller);
        do {
            cout << word << endl;
        } while (next_permutation(begin(word), end(word), is_first_smaller));
    }
}
