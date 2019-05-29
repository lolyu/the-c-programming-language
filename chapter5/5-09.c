#include <stdio.h>

int day_of_year(int, int, int);
int month_day(int, int, int *, int *);

int main(void) {
    int year, month, day, yday;
    year = 2000, month = 10, day = 20;
    printf("%d\n", yday = day_of_year(year, month, day));
    month_day(year, yday, &month, &day);
    printf("%d %d %d\n", year, month, day);
    return 0;
}

static char daytab[2][13] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int day_of_year(int year, int month, int day) {
    int leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if (year < 1752 || month < 0 || month > 12 || day < 1 || day > daytab[leap][month])
        return -1;
    char *start = *(daytab + leap);
    char *i = start + 1;
    while (i - start < month)
        day += *i++;
    return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday) {
    int leap;
    if (year < 1752 || yearday < 1)
        return -1;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if (yearday > (leap == 1 ? 366 : 365))
        return -1;
    char *i = *(daytab + leap) + 1;
    while (yearday > *i)
        yearday -= *i++;
    *pmonth = i - *(daytab + leap);
    *pday = yearday;
    return 0;
}
