#include <cstdio>

const int FIRST_YEAR = 1998;

int days_year[]      = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int days_leap_year[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is_leap_year(int year)
{
    return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

int count_days_year(int year)
{
    return is_leap_year(year) ? 366 : 365;
}

int count_days_until_year(int year)
{
    int result = 0;
    while (year-- > FIRST_YEAR) {
        result += count_days_year(year);
    }
    return result;
}

int* get_days_year(int year) {
    return is_leap_year(year) ? days_leap_year : days_year;
}

int count_days_until_month(int month, int year)
{
    int *days  = get_days_year(year);

    int result = 0;
    for (int i = 0; i < month; i++) {
        result += days[i];
    }
    return result;
}

int date_to_days(int day, int month, int year)
{
    int result;

    day--; month--;
    result += count_days_until_year(year);
    result += count_days_until_month(month, year);
    result += day;

    return result;
}

int days_to_year(int& days)
{
    int days_year, result = FIRST_YEAR;
    while (days >= (days_year = count_days_year(result))) {
        result++;
        days -= days_year;
    }
    return result;
}

int days_to_month(int& days, int year)
{
    int* days_year = get_days_year(year);
    int result = 0;
    while (days >= days_year[result]) {
        days -= days_year[result];
        result++;
    }
    return result;
}

void days_to_date(int days, int& day, int& month, int& year)
{
    year  = days_to_year(days);
    month = 1 + days_to_month(days, year);
    day   = 1 + days;
}

int main()
{
    int days, day, month, year;
    while (scanf("%d %d %d %d", &days, &day, &month, &year) != EOF && year) {
        days += date_to_days(day, month, year);
        days_to_date(days, day, month, year);
        
        printf("%d %d %d\n", day, month, year);
    }
}
