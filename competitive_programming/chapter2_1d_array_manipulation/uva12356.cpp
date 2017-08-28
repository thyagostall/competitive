#include <cstdio>

const int MAX = 100010;
const int NO = -1;

void init_array(int link_previous[], int link_next[], int soldier_qty)
{
    for (int i = 1; i <= soldier_qty; i++) {
        link_previous[i] = i - 1;
        link_next[i] = i + 1;
    }

    link_previous[1]       = NO;
    link_next[soldier_qty] = NO;
}

int main()
{
    int link_previous[MAX], link_next[MAX];
    int soldier_qty, loss_qty, first_loss, last_loss;

    while (scanf("%d %d", &soldier_qty, &loss_qty) != EOF && soldier_qty) {
        init_array(link_previous, link_next, soldier_qty);
        while (loss_qty--) {
            scanf("%d %d", &first_loss, &last_loss);
            link_next[link_previous[first_loss]] = link_next[last_loss];
            link_previous[link_next[last_loss]]  = link_previous[first_loss];

            if (link_previous[first_loss] == NO) {
                printf("*");
            } else {
                printf("%d", link_previous[first_loss]);
            }
            if (link_next[last_loss] == NO) {
                printf(" *\n");
            } else {
                printf(" %d\n", link_next[last_loss]);
            }
        }
        printf("-\n");
    }
}
