#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX = 1000;
const int MAX_RESULT = 4;

void print_square(char square[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c", square[i][j]);
        }
        printf("\n");
    }
    printf("--\n");
}

int rotate(char square[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            swap(square[i][j], square[j][i]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n / 2; j++) {
            swap(square[i][j], square[i][n - j - 1]);
        }
    }
}

bool are_equal(char small[MAX][MAX], char big[MAX][MAX], int offset_i, int offset_j, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (small[i][j] != big[i + offset_i][j + offset_j]) {
                return false;
            }
        }
    }
    return true;
}

void reset_result(int result[MAX_RESULT]) 
{
    for (int i = 0; i < MAX_RESULT; i++) {
        result[i] = 0;
    }
}

int main()
{
    int N, n;
    char big_square[MAX][MAX];
    char small_square[MAX][MAX];
    int result[MAX_RESULT];

    while (scanf("%d %d", &N, &n) != EOF && N && n) {
        reset_result(result);
        for (int i = 0; i < N; i++) {
            scanf("%s", big_square[i]);
        }
        for (int i = 0; i < n; i++) {
            scanf("%s", small_square[i]);
        }

        for (int angle = 0; angle < MAX_RESULT; angle++) {
            for (int i = 0; i < N - n + 1; i++) {
                for (int j = 0; j < N - n + 1; j++) {
                    if (are_equal(small_square, big_square, i, j, n)) {
                        result[angle]++;
                    }
                }
            }
            rotate(small_square, n);
        }

        for (int i = 0; i < MAX_RESULT; i++) {
            if (i)  printf(" ");
            printf("%d", result[i]);
        }
        printf("\n");
    }
}
