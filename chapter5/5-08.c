#include <stdio.h>

int main(void) {
    return 0;
}

static char daytab[2][13] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int day_of_year(int year, int month, int day) {
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if (year < 1752 || month < 0 || month > 12 || day < 1 || day > daytab[leap][month])
        return -1;
    for (i = 1; i < month; ++i)
        day += daytab[leap][i];
    return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;
    if (year < 1752 || yearday < 1)
        return -1;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if (yearday > (leap == 1 ? 366 : 365))
        return -1;
    for (i = 1; yearday > daytab[leap][i]; ++i)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
    return 0;
}
