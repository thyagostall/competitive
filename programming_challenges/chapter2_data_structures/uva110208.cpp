#include <iostream>
#include <cstdlib>

#define ASIZE 6

using namespace std;

int value(int round[ASIZE], int value) {
    int result = 0;
    for (int i = 0; i < 5; i++)
        if (round[i] == value)
            result += value;

    return result;
}

int sum_all(int round[ASIZE]) {
    int result = 0;
    for (int i = 0; i < 5; i++)
        result += round[i];

    return result;
}

int three_of_kind(int round[ASIZE]) {
    if (round[0] == round[2] || round[1] == round[3] || round[2] == round[4])
        return round[2] * 3;
    return 0;
}

int four_of_kind(int round[ASIZE]) {
    if (round[0] == round[3] || round[1] == round[4])
        return round[1] * 4;
    return 0;
}

int five_of_kind(int round[ASIZE]) {
    if (round[0] == round[4])
        return round[0];
    return 0;
}

int short_straight(int round[ASIZE]) {
    bool result;
    for (int t = 0; t < 2; t++) {
        result = true;
        for (int i = 1; i < 4; i++) {
            result &= round[i + t] - 1 == round[i + t - 1];
        }
    }

    if (result)
        return 25;
    else
        return 0;
}

int long_straight(int round[ASIZE]) {
    bool result = true;
    for (int i = 1; i < 5; i++) {
        result &= round[i] - 1 == round[i - 1];
    }

    if (result)
        return 35;
    else
        return 0;
}

int full_house(int round[ASIZE]) {
    if ((round[0] == round[1] && round[2] == round[4] && round[1] != round[2])
     || (round[0] == round[2] && round[3] == round[4] && round[2] != round[3]))
        return 40;
    return 0;
}

static int intcmp(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

int main() {
    int round[14][ASIZE], points[15], max, max_i, tmp, i, j, sum, bonus;
    bool used[15];

    for (i = 0; i < 13; i++) {
        for (j = 0; j < 5; j++)
            cin >> round[i][j];
        qsort(round[i], 5, sizeof(int), intcmp);
    }

    for (i = 0; i < 13; i++) {
        used[i] = false;
        points[i] = 0;
    }

    //values
    for (j = 0; j < 6; j++) {
        max = -1;
        for (i = 0; i < 13; i++) {
            if (used[i]) continue;

            tmp = value(round[i], j + 1);
            if (tmp > max)
                max = tmp, max_i = i;
        }
        points[j] = max;
        used[max_i] = true;

        cout << max_i << endl;
    }
    
    //full house
    max = -1;
    for (i = 0; i < 13; i++) {
        if (used[i]) continue;

        tmp = full_house(round[i]);
        if (tmp > max)
            max = tmp, max_i = i;
    }
    points[12] = max;
    used[max_i] = true;

    cout << max_i << endl;
    
    //three of a kind
    max = -1;
    for (i = 0; i < 13; i++) {
        if (used[i]) continue;

        tmp = three_of_kind(round[i]);
        if (tmp > max)
            max = tmp, max_i = i;
    }
    points[7] = max;
    used[max_i] = true;

    cout << max_i << endl;

    //four of a kind
    max = -1;
    for (i = 0; i < 13; i++) {
        if (used[i]) continue;

        tmp = four_of_kind(round[i]);
        if (tmp > max)
            max = tmp, max_i = i;
    }
    points[8] = max;
    used[max_i] = true;

    cout << max_i << endl;

    //five of a kind
    max = -1;
    for (i = 0; i < 13; i++) {
        if (used[i]) continue;

        tmp = five_of_kind(round[i]);
        if (tmp > max)
            max = tmp, max_i = i;
    }
    points[9] = 50;
    used[max_i] = true;

    cout << max_i << endl;
    
    //short straight
    max = -1;
    for (i = 0; i < 13; i++) {
        if (used[i]) continue;

        tmp = short_straight(round[i]);
        if (tmp > max)
            max = tmp, max_i = i;
    }
    points[10] = max;
    used[max_i] = true;

    cout << max_i << endl;
    
    //long straight
    max = -1;
    for (i = 0; i < 13; i++) {
        if (used[i]) continue;

        tmp = long_straight(round[i]);
        if (tmp > max)
            max = tmp, max_i = i;
    }
    points[11] = max;
    used[max_i] = true;

    cout << max_i << endl;
    
    //sum
    max = -1;
    for (i = 0; i < 13; i++) {
        if (used[i]) continue;

        tmp = sum_all(round[i]);
        if (tmp > max)
            max = tmp, max_i = i;
    }
    points[6] = max;
    used[max_i] = true;

    cout << max_i << endl;

    //sum the points
    sum = 0;
    bonus = 0;
    for (i = 0; i < 13; i++) {
        sum += points[i];
        if (i == 5 && sum > 63)
            bonus = 35;
        cout << points[i] << " ";
    }
    cout << bonus << " " << sum << endl;        
}
