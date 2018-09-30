#include <iostream>
#include <cmath>
#include <iomanip>

#define NO_SOLUTION -1
#define EPS 1e-9

using namespace std;

bool has_solution(int p, int q, int r, int s, int t, int u);
double compute_solution(int p, int q, int r, int s, int t, int u);
double solve(double x, int p, int q, int r, int s, int t, int u);

int main()
{
    int p, q, r, s, t, u;

    cout << fixed << setprecision(4);
    while (cin >> p >> q >> r >> s >> t >> u) {
        if (has_solution(p, q, r, s, t, u)) {
            cout << compute_solution(p, q, r, s, t, u) << endl;
        } else {
            cout << "No solution" << endl;
        }
    }
}

bool has_solution(int p, int q, int r, int s, int t, int u)
{
    return solve(0, p, q, r, s, t, u) * solve(1, p, q, r, s, t, u) <= 0;
}

double compute_solution(int p, int q, int r, int s, int t, int u)
{
    double solution = NO_SOLUTION;
    double lo = 0.0, hi = 1.0;
    while (lo + EPS < hi) {
        double x = (lo + hi) / 2;
        if (solve(lo, p, q, r, s, t, u) * solve(x, p, q, r, s, t, u) <= 0.0)
            hi = x;
        else
            lo = x;
    }
    solution = (lo + hi) / 2;
    return solution;
}

double solve(double x, int p, int q, int r, int s, int t, int u)
{
    return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

