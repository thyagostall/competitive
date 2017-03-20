#include <cstdio>
#include <climits>

#define EXIT_MIN 3
#define MAX_TL 100
#define ARRAY_TL MAX_TL + 2
#define MAX_SEC 60 * 60 * 5

#define GREEN 10
#define ORANGE 20
#define RED 30

void print_formatted_time(int time)
{
    int h, m, s;
    s = time % 60;
    time /= 60;
    m = time % 60;
    time /= 60;
    h = time;
    
    printf("%02d:%02d:%02d\n", h, m, s);
}

int get_tl_color(int tl, int time)
{
    time = time % (2 * tl);
    if (time >= tl) {
        return RED;
    } else if (time >= tl - 5) {
        return ORANGE;
    } else {
        return GREEN;
    }
}

bool all_green(int traffic_lights[], int size, int time) 
{
    int i;
    for (i = 0; i < size; i++) {
        if (get_tl_color(traffic_lights[i], time) != GREEN) {
            return false;
        }
    }
    return true;
}

int main()
{
    int traffic_lights[MAX_TL];
    int exit_flag, t, q, time, min;

    bool success;

    exit_flag = 0;
    while (exit_flag < EXIT_MIN) {
        q = 0;
        min = INT_MAX;
        while (scanf("%d", &t) != EOF && t > 0) {
            exit_flag = 0;
            traffic_lights[q++] = t;
            min = min < t ? min : t;
        }
        if (!exit_flag) {
            success = false;
            for (time = 2 * min; time <= MAX_SEC; time++) {
                if (all_green(traffic_lights, q, time)) {
                    success = true;
                    break;
                }
            }

            if (success) {
                print_formatted_time(time);
            } else {
                printf("Signals fail to synchronise in 5 hours\n");
            }
        }
        exit_flag++;
    }
}
