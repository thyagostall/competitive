#include <cstdio>
#include <vector>

using namespace std;

int abs(int n) {
    return n >= 0 ? n : n * -1;
}

bool is_jolly(vector<int>& sequence)
{
    int size = sequence.size();
    if (size == 1) {
        return true;
    }
    
    vector<bool> differences(size + 1);
    for (int i = 1; i < size; i++) {
        int d = abs(sequence[i - 1] - sequence[i]);
        differences[d] = true;
    }

    for (int i = 1; i < size; i++) {
        if (!differences[i]) {
            return false;
        }
    }
    return true;
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF && n) {
        vector<int> sequence(n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &sequence[i]);
        }

        if (is_jolly(sequence)) {
            printf("Jolly\n");
        } else {
            printf("Not jolly\n");
        }
    }
}
