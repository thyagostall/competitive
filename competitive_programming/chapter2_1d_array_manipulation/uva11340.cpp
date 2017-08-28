#include <iostream>
#include <iomanip>

using namespace std;

const int CHAR_QTY = 300;

void flush()
{
    string line;
    getline(cin, line);
}

bool is_in_interval(char i)
{
    return 0 <= i && i < CHAR_QTY;
}

int calculate_line_price(int price_characters[CHAR_QTY], string line)
{
    int result = 0;
    for (auto c : line) {
        if (is_in_interval(c)) {
            result += price_characters[c];
        }
    }
    return result;
}

void zero_fill(int price_characters[CHAR_QTY])
{
    for (int i = 0; i < CHAR_QTY; i++) {
        price_characters[i] = 0;
    }
}

int main()
{
    int test_cases, paid_characters_quantity, text_line_quantity, final_value;
    int paid_characters[CHAR_QTY];
    char character;
    string line;

    cin >> test_cases;
    while (test_cases--) {
        zero_fill(paid_characters);

        cin >> paid_characters_quantity;
        for (int i = 0; i < paid_characters_quantity; i++) {
            cin >> character;
            cin >> paid_characters[character];
        }
        cin >> text_line_quantity;
        
        flush();
        final_value = 0;
        while (text_line_quantity--) {
            getline(cin, line);
            final_value += calculate_line_price(paid_characters, line);
        }
        cout << setprecision(2) << fixed << final_value / 100. << "$" << endl;
    }
}
