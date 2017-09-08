#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    int test_cases, ferry_length, car_qty, length;
    char buff[10];

    scanf("%d", &test_cases);
    while (test_cases--) {
        scanf("%d %d", &ferry_length, &car_qty);
        ferry_length = ferry_length * 100;

        queue<int> left, right, *tmp;
        queue<int> *current = &left;
        queue<int> *other = &right;

        while (car_qty--) {
            scanf("%d %s", &length, buff);

            if (strcmp("right", buff) == 0)
                right.push(length);
            else
                left.push(length);
        }
    
        int cross_qty = 0, ferry_used_length = 0;
        while (!left.empty() || !right.empty()) {
            while (!current->empty() && ferry_used_length + current->front() <= ferry_length) {
                ferry_used_length += current->front();
                current->pop();
            }

            tmp = current;
            current = other;
            other = tmp;
            
            ferry_used_length = 0;
            cross_qty++;
        }

        printf("%d\n", cross_qty);
    }
}
