#include <iostream>
#include <queue>
#include <stack>

using namespace std;

class Queue: public queue<int>
{
public:
    bool pop_and_check(int x)
    {
        if (this->empty()) return false;

        int candidate = this->front();
        this->pop();
        return x == candidate;
    }
};

class Stack: public stack<int>
{
public:
    bool pop_and_check(int x)
    {
        if (this->empty()) return false;

        int candidate = this->top();
        this->pop();
        return x == candidate;
    }
};

class PriorityQueue: public priority_queue<int>
{
public:
    bool pop_and_check(int x)
    {
        if (this->empty()) return false;

        int candidate = this->top();
        this->pop();
        return x == candidate;
    }
};

bool is_not_sure(bool a, bool b, bool c)
{
    if ((a && b && c) || a && b || a && c || b && c) 
        return true;
    else 
        return false;
}

int main() {
    int quantity;
    while (cin >> quantity) {
        Queue queue;
        Stack stack;
        PriorityQueue priority_queue;

        bool is_q = true, is_s = true, is_pq = true;

        while (quantity--) {
            int op, x;
            cin >> op >> x;

            if (op == 1) {
                queue.push(x);
                stack.push(x);
                priority_queue.push(x);
            } else {
                is_q &= queue.pop_and_check(x);
                is_s &= stack.pop_and_check(x);
                is_pq &= priority_queue.pop_and_check(x);
            }
        }

        if (is_not_sure(is_q, is_s, is_pq)) {
            cout << "not sure" << endl;
        } else if (is_q) {
            cout << "queue" << endl;
        } else if (is_s) {
            cout << "stack" << endl;
        } else if (is_pq) {
            cout << "priority queue" << endl;
        } else {
            cout << "impossible" << endl;
        }
    }
}
