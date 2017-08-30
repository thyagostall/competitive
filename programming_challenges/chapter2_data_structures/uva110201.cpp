#include <cstdio>
#include <cstdlib>
#include <cmath>

#define SIZE 3001

bool contains(int list[], int list_size, int number) {
    int i;
    for (i = 0; i < list_size; i++)
        if (list[i] == number)
            return true;

    return false;
}

int main() {
    int i, value, list_size;
    int list[SIZE], touched[SIZE];
    bool result;

    while (scanf("%d", &list_size) != EOF) {
        for (i = 0; i < list_size; i++) {
            scanf("%d", &list[i]);
            touched[i] = 0;
        }

        for (i = 0; i < list_size - 1; i++) {
            value = list[i] - list[i + 1];
            value = abs(value);

            if (value > 0 && value < list_size)
                touched[value - 1]++;
        }
        
        result = true;
        for (i = 0; i < list_size - 1; i++) {
            result &= touched[i];
        }

        if (result)
            printf("Jolly\n");
        else
            printf("Not jolly\n");
    }

    return EXIT_SUCCESS;
}
