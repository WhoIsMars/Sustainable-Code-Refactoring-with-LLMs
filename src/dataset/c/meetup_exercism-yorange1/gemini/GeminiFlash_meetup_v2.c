#include "meetup.h"
#include <time.h>
#include <string.h>

static const char *weekdays[] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

static const unsigned int days_in_month[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

static unsigned int weekday_to_num(const char *weekday)
{
    for (unsigned int i = 0; i < 7; i++)
        if (weekdays[i][0] == weekday[0] && !strcmp(weekdays[i], weekday)) // Optimized string comparison
            return i;
    return 8;
}

static unsigned int is_leap(unsigned int year)
{
    return (!(year % 4) && (year % 100 != 0)) || !(year % 400); // Optimized leap year calculation
}

int meetup_day_of_month(unsigned int year,
                        unsigned int month,
                        const char *week,
                        const char *day_of_week)
{
    int wday = weekday_to_num(day_of_week);
    if (wday > 6)
        return -1;

    struct tm tm = {
        .tm_year = year - 1900,
        .tm_mon = month - 1,
        .tm_mday = 1,
    };

    time_t t = mktime(&tm);
    if (t == -1)
        return -1;

    struct tm tm_result;
    localtime_r(&t, &tm_result);

    int day = 1 + wday - tm_result.tm_wday;
    if (day <= 0)
        day += 7;

    if (week[0] == 'f' && !strcmp(week, "first"))
    {
        return day;
    }
    else if (week[0] == 's' && !strcmp(week, "second"))
    {
        return day + 7;
    }
    else if (week[0] == 't' && !strcmp(week, "third"))
    {
        return day + 14;
    }
    else if (week[0] == 'f' && !strcmp(week, "fourth"))
    {
        return day + 21;
    }
    else if (week[0] == 'l' && !strcmp(week, "last"))
    {
        int ndays = days_in_month[is_leap(year)][month - 1];
        return (day + 28) > ndays ? day + 21 : day + 28;
    }
    else if (week[0] == 't' && !strcmp(week, "teenth"))
    {
        return (day + 7) < 13 ? day + 14 : day + 7;
    }

    return -1;
}