#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define LINE_LENGTH 50
#define CONTESTANT_QTY 101

using namespace std;

typedef struct {
    bool is_participating;
    int contestant_number;
    int problems_solved;
    int penalty_time;
    int tries[10];
    bool solved[10];
} contestant_t;

void reset_contestants(contestant_t contestants[CONTESTANT_QTY])
{
    for (int i = 0; i < CONTESTANT_QTY; i++) {
        contestants[i].is_participating = false;
        contestants[i].contestant_number = i;
        contestants[i].problems_solved = 0;
        contestants[i].penalty_time = 0;
        for (int j = 1; j <= 9; j++) {
            contestants[i].solved[j] = false;
            contestants[i].tries[j] = 0;
        }
    }
}

bool compare(contestant_t a, contestant_t b)
{
    if (a.problems_solved > b.problems_solved) {
        return true;
    } else if (a.problems_solved == b.problems_solved) {
        if (a.penalty_time < b.penalty_time) {
            return true;
        } else if (a.penalty_time == b.penalty_time) {
            if (a.contestant_number < b.contestant_number) {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int test_cases, contestant, problem, time, unsolved_penalty;
    char buffer[LINE_LENGTH], veredict;
    contestant_t contestants[CONTESTANT_QTY];

    scanf("%d\n\n", &test_cases);
    while (test_cases--) {
        reset_contestants(contestants);

        while (fgets(buffer, LINE_LENGTH, stdin) && strlen(buffer) > 1) {
            sscanf(buffer, "%d %d %d %c\n", &contestant, &problem, &time, &veredict);

            contestants[contestant].is_participating = true;
            if (veredict == 'C') {
                if (!contestants[contestant].solved[problem]) {
                    contestants[contestant].problems_solved++;
                    contestants[contestant].solved[problem] = true;
                    unsolved_penalty = 20 * contestants[contestant].tries[problem];
                    contestants[contestant].penalty_time += time + unsolved_penalty;
                }
            } else if (veredict == 'I') {
                contestants[contestant].tries[problem]++;
            }
        }

        stable_sort(begin(contestants), end(contestants), compare);
        for (int i = 0; i < CONTESTANT_QTY; i++) {
            if (contestants[i].is_participating) {
                printf("%d %d %d\n", 
                        contestants[i].contestant_number, 
                        contestants[i].problems_solved, 
                        contestants[i].penalty_time
                        );
            }
        }
        if (test_cases) printf("\n");
    }
}
