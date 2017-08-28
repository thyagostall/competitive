#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

void print_set(set<char> a)
{
    for (auto x : a) {
        printf("%c ", x);
    }
    printf("\n");
}

void print_sets(vector<set<char> > sets)
{
    for (auto set : sets) {
        print_set(set);
    }
}

set<char> operator+(set<char> a, set<char> b)
{
    set<char> result;
    for (auto x : a) {
        result.insert(x);
    }

    for (auto x : b) {
        result.insert(x);
    }

    return result;
}

set<char> operator*(set<char> a, set<char> b)
{
    set<char> result;
    for (auto x : a) {
        for (auto y : b) {
            if (x == y) {
                result.insert(x);
            }
        }
    }
    return result;
}

set<char> operator-(set<char> a, set<char> b)
{
    set<char> result;
    for (auto x : a) {
        if (find(b.begin(), b.end(), x) != b.end()) {
            continue;
        }

        result.insert(x);
    }
    return result;
}

set<char> intersect_all(vector<set<char> > sets)
{
    set<char> result = sets[0];
    for (auto set : sets) {
        result = result * set;
    }
    return result;
}

set<char> union_all(vector<set<char> > sets)
{
    set<char> result = sets[0];
    for (auto set : sets) {
        result = result + set;
    }
    return result;
}

set<char> to_set(char *coins)
{
    set<char> result;
    int len = strlen(coins);
    for (int i = 0; i < len; i++) {
        result.insert(coins[i]);
    }
    return result;
}

int main()
{
    int t, i;
    char coins_left[10], coins_right[10], result[5];
    scanf("%d", &t);
    while (t--) {
        vector<set<char> > ups, downs;
        set<char> up, down, even;
        
        for (i = 0; i < 3; i++) {
            scanf("%s %s %s", coins_left, coins_right, result);

            if (strcmp(result, "up") == 0) {
                downs.push_back(to_set(coins_left));
                ups.push_back(to_set(coins_right));
            } else if (strcmp(result, "down") == 0) {
                ups.push_back(to_set(coins_left));
                downs.push_back(to_set(coins_right));
            } else {
                even = even + to_set(coins_left);
                even = even + to_set(coins_right);
            }
        }

        up = intersect_all(ups);
        down = intersect_all(downs);

        up = up - even;
        down = down - even;

        if (!up.empty()) {
            printf("%c is the counterfeit coin and it is light.\n", *up.begin());
        }
        
        if (!down.empty()) {
            printf("%c is the counterfeit coin and it is heavy.\n", *down.begin());
        }
    }
}
