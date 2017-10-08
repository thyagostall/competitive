#include <iostream>
#include <limits>

#define MAX 1000 

using namespace std;

int manhattan(int i, int j, int p, int q)
{
    return abs(i - p) + abs(j - q);
}

int main()
{
    int size, result, round, i, j;
    string line;
    char maze[MAX][MAX];

    while (cin >> size) {
        for (int i = 0; i < size; i++) {
            cin >> line;
            for (int j = 0; j < size; j++) {
                maze[i][j] = line[j];
            }
        }

        int answer = numeric_limits<int>::min();
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                if (maze[i][j] != '1') 
                    continue;

                result = numeric_limits<int>::max();
                for (int p = 0; p < size; p++) {
                    for (int q = 0; q < size; q++) {
                        if (maze[p][q] == '3')
                            result = min(result, manhattan(i, j, p, q));
                    }
                }
                answer = max(answer, result);
            }
        }
        cout << answer << endl;
    }
}
