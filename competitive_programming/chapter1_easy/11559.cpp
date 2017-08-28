#include <cstdio>
#include <climits>

using namespace std;

const int INFINITY = INT_MAX;

int min(int a, int b) {
    return a < b ? a : b;
}

int main() 
{
    int N, B, H, W;
    int P, A, w, h;
    int result;

    while (scanf("%d %d %d %d", &N, &B, &H, &W) != EOF) {
        result = INFINITY;
        for (h = 0; h < H; h++) {
            scanf("%d", &P);
            for (w = 0; w < W; w++) {
                scanf("%d", &A);
                if (N <= A && N * P <= B) {
                    result = min(result, N * P);
                }
            }
        }
        if (result < INFINITY) {
            printf("%d\n", result);
        } else {
            printf("stay home\n");
        }
    }
}
