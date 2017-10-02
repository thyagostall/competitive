#include <iostream>
#include <vector>

using namespace std;

typedef struct 
{
    string brand_name;
    int min_price;
    int max_price;
} BrandHist;

class Database: public vector<BrandHist>
{
public:
    string get_single_one(int price)
    {
        int count = 0;
        BrandHist last;
        for (auto &item : (*this)) {
            if (item.min_price <= price && price <= item.max_price) {
                last = item;
                count++;
            }
        }
        if (count == 1) {
            return last.brand_name;
        }

        return "UNDETERMINED";
    }
};

int main()
{
    int test_cases, database_size, min_price, max_price, query_qty, query;
    string brand_name;

    cin >> test_cases;
    while (test_cases--) {
        cin >> database_size;
        Database database;
        while (database_size--) {
            cin >> brand_name >> min_price >> max_price;

            BrandHist item {brand_name, min_price, max_price};
            database.push_back(item);
        }
        cin >> query_qty;
        while (query_qty--) {
            cin >> query;
            cout << database.get_single_one(query) << endl;
        }
        if (test_cases) cout << endl;
    }
}
