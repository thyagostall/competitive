#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

istream &operator>>(istream &in, vector<int> &v);
ostream &operator<<(ostream &out, vector<int> &v);
pair<int, int> compute(vector<int> &book_prices, int money);
vector<int> reject_above_price(vector<int> &book_prices, int reject_above_amount);

int main()
{
    int book_qty, money;
    while (cin >> book_qty) {
        vector<int> book_prices(book_qty, 0);
        cin >> book_prices;
        cin >> money;

        pair<int, int> result = compute(book_prices, money);
        cout << "Peter should buy books whose prices are " 
             << result.first
             << " and " 
             << result.second
             << "." << endl << endl;
    }
}

pair<int, int> compute(vector<int> &book_prices, int money)
{
    sort(book_prices.begin(), book_prices.end());

    int reject_above_amount = money - book_prices[0];
    book_prices = reject_above_price(book_prices, reject_above_amount);    

    pair<int, int> result {0, numeric_limits<int>::max()};
    for (int i = 0; i < book_prices.size(); i++) {
        for (int j = i + 1; j < book_prices.size(); j++) {
            if (book_prices[i] + book_prices[j] == money 
                    && book_prices[j] - book_prices[i] < result.second - result.first) {
                result = {book_prices[i], book_prices[j]};
            }
        }
    }
    return result;
}

vector<int> reject_above_price(vector<int> &book_prices, int reject_above_amount)
{
    vector<int>::iterator new_end = upper_bound(book_prices.begin(), book_prices.end(), reject_above_amount);
    return { book_prices.begin(), new_end };
}

istream &operator>>(istream &in, vector<int> &v)
{
    for (int i = 0; i < v.size(); i++)
        in >> v[i];
    return in;
}

ostream &operator<<(ostream &out, vector<int> &v)
{
    for (auto i : v)
        out << i << " ";
    return out;
}
