#include <iostream>
#include <vector>

using namespace std;

class FenwickTree
{
public:
    FenwickTree(int size): table(size)
    {
        this->size = size;
        table.assign(size, 0);
    }

    void update(int i, int delta)
    {
        while (i < size) {
            table[i] += delta;
            i += lowest_one_bit(i);
        }
    }

    int sum(int i)
    {
        int result = 0;
        while (i) {
            result += table[i];
            i -= lowest_one_bit(i);
        }
        return result;
    }

    int range_sum(int i, int j)
    {
        return sum(j) - sum(i - 1);
    }
private:
    int size;
    std::vector<int> table;

    int lowest_one_bit(int i)
    {
        return i & -i;
    }
};

int main()
{
    int size, queries, first, second;
    char query;
    while (cin >> size >> queries) {
        size++;
        FenwickTree negatives(size), zeroes(size);
        vector<int> input(size);
        for (int i = 1; i < size; i++) {
            cin >> input[i];
            if (input[i] == 0) 
                zeroes.update(i, 1);
            else if (input[i] < 0)
                negatives.update(i, 1);
        }

        while (queries--) {
            cin.ignore(1, '\n');
            cin >> query >> first >> second;

            if (query == 'P') {
                if (zeroes.range_sum(first, second)) 
                    cout << "0";
                else if (negatives.range_sum(first, second) % 2) 
                    cout << "-";
                else 
                    cout << "+";
            } else {
                if (input[first] >= 0 && second < 0)
                    negatives.update(first, 1);
                else if (input[first] < 0 && second >= 0)
                    negatives.update(first, -1);

                if (input[first] != 0 && second == 0)
                    zeroes.update(first, 1);
                else if (input[first] == 0 && second != 0)
                    zeroes.update(first, -1);

                input[first] = second;
            }
        }
        cout << endl;
    }
}
