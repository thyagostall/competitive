#include <cstdio>

using namespace std;

int main()
{
    double down, loan, depreciation_rate;
    int month, months, records_qty;

    while (scanf("%d %lf %lf %d", &months, &down, &loan, &records_qty) && months >= 0) {
        printf("%d %lf %lf %d\n", months, down, loan, records_qty);
        while (records_qty--) {
            scanf("%d %lf", &month, &depreciation_rate);
            printf("%d %lf\n", month, depreciation_rate);
        }
    }
}
