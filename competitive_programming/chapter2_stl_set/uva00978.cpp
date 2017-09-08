#include <iostream>
#include <set>

using namespace std;

class Army: public multiset<int>
{
public:
    int extract_max() 
    {
        multiset<int>::iterator last = prev(this->end());
        int result = *last;
        this->erase(last);
        return result;
    }

    void pump_all(Army &other)
    {
        while (!other.empty()) this->insert(other.extract_max());
    }
};

void compute_battle(int &green, int &blue)
{
    int ini_green = green, ini_blue = blue;
    green = ini_green - ini_blue;
    blue = ini_blue - ini_green;
}

int main()
{
    int test_cases, buff;

    cin >> test_cases;
    while (test_cases--) {
        int battle_fields, green_qty, blue_qty;
        Army green_army, blue_army;
        Army green_temp, blue_temp;

        cin >> battle_fields >> green_qty >> blue_qty;
        while (green_qty--) {
            cin >> buff;
            green_army.insert(buff);
        }
        while (blue_qty--) {
            cin >> buff;
            blue_army.insert(buff);
        }

        while (!green_army.empty() && !blue_army.empty()) {
            int available_battle_fields = battle_fields;
            while (available_battle_fields-- && !green_army.empty() && !blue_army.empty()) {
                int green = green_army.extract_max();
                int blue = blue_army.extract_max();
                
                compute_battle(green, blue);
                
                if (green > 0) 
                    green_temp.insert(green);
                if (blue > 0) 
                    blue_temp.insert(blue);
            }

            green_army.pump_all(green_temp);
            blue_army.pump_all(blue_temp);
        }

        if (green_army.empty() && blue_army.empty()) {
            cout << "green and blue died" << endl;
        } else if (blue_army.empty()) {
            cout << "green wins" << endl;

            while (!green_army.empty()) {
                cout << green_army.extract_max() << endl;
            }
        } else {
            cout << "blue wins" << endl;

            while (!blue_army.empty()) {
                cout << blue_army.extract_max() << endl;
            }
        }

        if (test_cases) cout << endl;
    }
}
