#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

bool should_wait(vector<int> *car_arrivals, queue<int> *current, queue<int> *other)
{
    if (current->empty()) return false;

    if (other->empty()) return true;

    return (*car_arrivals)[current->front()] <= (*car_arrivals)[other->front()];
}

bool should_wait_other(vector<int> *car_arrivals, queue<int> *other, int ferry_time)
{
    if (other->empty()) return false;

    return (*car_arrivals)[other->front()] > ferry_time;
}

int main()
{
    int test_cases, ferry_capacity, time_cross, car_qty, time;
    char buff[10];

    scanf("%d", &test_cases);
    while (test_cases--) {
        scanf("%d %d %d", &ferry_capacity, &time_cross, &car_qty);

        queue<int> left, right, *tmp;
        queue<int> *current = &left;
        queue<int> *other = &right;

        vector<int> car_arrivals(car_qty, 0);

        for (int i = 0; i < car_qty; i++) {
            scanf("%d %s", &time, buff);
            car_arrivals[i] = time;

            if (strcmp("right", buff) == 0)
                right.push(i);
            else
                left.push(i);
        }

        queue<int> ferry;
        int ferry_time = 0;

        while (!left.empty() || !right.empty()) {
            while (!current->empty() && ferry.size() < ferry_capacity && car_arrivals[current->front()] <= ferry_time) {
                ferry.push(current->front());
                current->pop();
            }

            if (ferry.size() > 0) {
                ferry_time += time_cross;
            } else if (should_wait(&car_arrivals, current, other)) {
                ferry_time = car_arrivals[current->front()], ferry_time;
                continue;
            } else if (should_wait_other(&car_arrivals, other, ferry_time)) {
                ferry_time = car_arrivals[other->front()] + time_cross;
            } else {
                ferry_time += time_cross;
            }

            tmp = current;
            current = other;
            other = tmp;
            
            while (!ferry.empty()) {
                car_arrivals[ferry.front()] = ferry_time;
                ferry.pop();
            }
        }

        for (int i = 0; i < car_qty; i++) {
            printf("%d\n", car_arrivals[i]);
        }
        if (test_cases) printf("\n");
    }
}
