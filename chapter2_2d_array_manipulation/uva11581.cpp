#include <cstdio>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> neighbors {
    pair<int, int>(0, 1),
    pair<int, int>(0, -1),
    pair<int, int>(1, 0),
    pair<int, int>(-1, 0),
};

bool is_all_zeros(int grid[3][3])
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j]) return false;
        }
    }
    return true;
}

bool is_in_bounds(pair<int, int> p, int i, int j)
{
    return i + p.first >= 0 && i + p.first < 3 && j + p.second >= 0 && j + p.second < 3;
}

void apply_f(int grid[3][3])
{
    int temp[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp[i][j] = 0;
            for (auto p : neighbors) {
                if (!is_in_bounds(p, i, j)) continue;
                temp[i][j] += grid[i + p.first][j + p.second];
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            grid[i][j] = temp[i][j] % 2;
        }
    }
}

void print_grid(int grid[3][3])
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int test_cases;
    int grid[3][3];
    
    scanf("%d", &test_cases);
    while (test_cases--) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                scanf("%1d", &grid[i][j]);
            }
        }

        int result = 0;
        while (!is_all_zeros(grid)) {
            apply_f(grid);
            result++;
        }
        printf("%d\n", result - 1);
    }
}
