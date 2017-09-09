#include <iostream>
#include <queue>

using namespace std;

typedef struct _instruction {
    int query_number;
    int period;
    int current;

    bool operator<(const struct _instruction &other) const {
        if (this->current == other.current)
            return !(this->query_number < other.query_number);
        
        return !(this->current < other.current);
    }
} Instruction;

int main()
{
    string command;
    int buff_query, buff_period, query_qty;
    priority_queue<Instruction> stream;

    while (cin >> command && command != "#") {
        cin >> buff_query;
        cin >> buff_period;
        stream.push(Instruction{buff_query, buff_period, buff_period});                
    }

    cin >> query_qty;

    while (query_qty--) {
        Instruction i = stream.top();
        stream.pop();
        stream.push(Instruction{i.query_number, i.period, i.current + i.period});

        cout << i.query_number << endl;
    }
}
