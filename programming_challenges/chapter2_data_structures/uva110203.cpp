#include <cstdio>
#include <cstdlib>

#define WEEK_SIZE 7

typedef enum {
    saturday, 
    sunday,
    monday,
    tuesday,
    wednesday,
    thursday,
    friday
} week_day;

int main() {
    int test_case_qty, day_qty, party_qty;
    int days_lost;
    int i, j;
    int hartal_parameter[100];

    bool strike_this_day;

    scanf("%d", &test_case_qty);

    while (test_case_qty-- > 0) {
        days_lost = 0;
        scanf("%d", &day_qty);
        scanf("%d", &party_qty);

        for (i = 0; i < party_qty; i++) {
            scanf("%d", &hartal_parameter[i]);
        }

        for (i = 1; i <= day_qty; i++) {
            if (i % WEEK_SIZE == friday || i % WEEK_SIZE == saturday)
                continue;
            
            strike_this_day = false;
            for (j = 0; j < party_qty; j++) {
                if (i % hartal_parameter[j] == 0) {
                    strike_this_day = true;
                    break;
                }
            }

            if (strike_this_day)
                days_lost++;
        }

        printf("%d\n", days_lost);
    }

    return EXIT_SUCCESS;
}
