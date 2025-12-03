#include "meetup.h"
#include <time.h>
#include <string.h>

static const unsigned int days_in_month[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

static unsigned int weekday_to_num(const char *weekday)
{
    switch (weekday[0])
    {
    case 'S':
        return weekday[1] == 'u' ? 0 : 6; // Sunday or Saturday
    case 'M':
        return 1; // Monday
    case 'T':
        return weekday[1] == 'u' ? 2 : 4; // Tuesday or Thursday
    case 'W':
        return 3; // Wednesday
    case 'F':
        return 5; // Friday
    default:
        return 8; // Invalid
    }
}

static unsigned int is_leap(unsigned int year)
{
    return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

int meetup_day_of_month(unsigned int year,
                        unsigned int month,
                        const char *week,
                        const char *day_of_week)
{
    int wday = weekday_to_num(day_of_week);
    if (wday > 7)
        return -1;

    struct tm tm = {
        .tm_year = year - 1900,
        .tm_mon = month - 1,
        .tm_mday = 1,
    };
    mktime(&tm);

    int day = 1 + (wday - tm.tm_wday + 7) % 7;

    if (strcmp(week, "first") == 0)
        return day;
    if (strcmp(week, "second") == 0)
        return day + 7;
    if (strcmp(week, "third") == 0)
        return day + 14;
    if (strcmp(week, "fourth") == 0)
        return day + 21;
    if (strcmp(week, "last") == 0)
    {
        int ndays = days_in_month[is_leap(year)][month - 1];
        return (day + 28 > ndays) ? day + 21 : day + 28;
    }
    if (strcmp(week, "teenth") == 0)
        return day + (day + 6 < 13 ? 7 : 0);

    return -1;
}