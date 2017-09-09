#include <iostream>
#include <queue>

using namespace std;

typedef struct _value {
    int value;

    bool operator<(const struct _value &other) const
    {
        return !(this->value < other.value);
    }
} Value;

class MinPriorityQueue: public priority_queue<Value>
{
public:
    int min()
    {
        int result = this->top().value;
        this->pop();
        return result;
    }

    void push(int value)
    {
        priority_queue<Value>::push(Value {value});
    }
};

int main()
{
    int quantity, buff;
    while (cin >> quantity && quantity) {
        MinPriorityQueue sum;
        while (quantity--) {
            cin >> buff;
            sum.push(buff);
        }

        int local, total = 0;
        while (sum.size() > 1) {
            local = sum.min() + sum.min();
            total += local;
            sum.push(local);
        }
        cout << total << endl;
    }
}
