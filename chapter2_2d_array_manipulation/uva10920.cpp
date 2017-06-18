#include <cstdio>
#include <cmath>
#include <utility>

using namespace std;

typedef unsigned long long ull;

void walk_cycle(ull& i, ull& j, ull& index, ull step)
{
    i++, index--;
    if (!index) return;

    for (ull x = 0; x < step - 1; x++) {
        j--; index--;
        if (!index) return;
    }
    for (ull x = 0; x < step; x++) {
        i--, index--;
        if (!index) return;
    }
    for (ull x = 0; x < step; x++) {
        j++, index--;
        if (!index) return;
    }
    for (ull x = 0; x < step; x++) {
        i++, index--;
        if (!index) return;
    }
}

ull floor_odd(double input)
{
    ull result = (ull) input;
    if (result % 2 == 0) {
        result--;
    }
    return result;
}

pair<ull, ull> get_coordinates(ull side, ull index)
{
    ull i, j, step;
    i = j = ceil(side / 2.);
    
    ull small = floor_odd(sqrt(index));
    ull x = small / 2;
    ull y = small / 2;

    i = i + x;
    j = j + y;

    index -= small * small;
    step = small + 1;
    
    while (index) {
        walk_cycle(i, j, index, step);
        step += 2;
    }

    return pair<ull, ull>(i, j);
}

int main()
{
    ull side, index;
    while (scanf("%lld %lld", &side, &index) != EOF && side) {
        pair<ull, ull> result = get_coordinates(side, index);
        printf("Line = %lld, column = %lld.\n", result.first, result.second);
    }
}
