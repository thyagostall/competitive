#include <iostream>

using namespace std;

bool find_solution(int a, int b, int c, int &x, int &y, int &z)
{
    for (x = -1000; x <= 3 * a; x++) {
        for (y = -1000; y <= a + 2 * b; y++) {
            z = a - x - y;
            if (x != y && y != z && x != z && 
                    x + y + z == a &&
                    x * y * z == b &&
                    x * x + y * y + z * z == c) {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int test_cases, a, b, c, x, y, z;
    cin >> test_cases;
    while (test_cases--) {
        cin >> a >> b >> c;
        if (find_solution(a, b, c, x, y, z)) {
            cout << x << " " << y << " " << z << endl;
        } else {
            cout << "No solution." << endl;
        }
    }
}
