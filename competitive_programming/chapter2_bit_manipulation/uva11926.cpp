#include <cstdio>
#include <bitset>

#define BIT_SET_SIZE 1000010
#define M 1000000

using namespace std;

int main()
{
    bitset<BIT_SET_SIZE> tasks;
    int normal, multi, start, end, interval;
    bool conflict;
    while (scanf("%d %d", &normal, &multi) && (normal || multi)) {
        conflict = false;
        tasks.reset();

        while (normal--) {
            scanf("%d %d", &start, &end);
            for (int i = start; i < end && !conflict; i++) {
                if (tasks.test(i)) conflict = true;
                tasks.set(i);
            }
        }
        while (multi--) {
            scanf("%d %d %d", &start, &end, &interval);
            while (start < M) {
                for (int i = start; i < end && !conflict; i++) {
                    if (tasks.test(i)) conflict = true;
                    tasks.set(i);
                }
                start += interval;
                end += interval;
                end = min(end, M);
            }
        }

        if (conflict) {
            printf("CONFLICT\n");
        } else {
            printf("NO CONFLICT\n");
        }
    }
}
