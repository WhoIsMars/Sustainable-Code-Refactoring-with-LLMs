#include "meetup.h"
#include <time.h>
#include <string.h>

static const char weekdays[7][10] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

static const unsigned char days_in_month[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static unsigned int weekday_to_num(const char *weekday)
{
    const char first_char = weekday[0];
    const char second_char = weekday[1];
    
    switch (first_char) {
        case 'S':
            return (second_char == 'u') ? 0 : 6;
        case 'M':
            return 1;
        case 'T':
            return (second_char == 'u') ? 2 : 4;
        case 'W':
            return 3;
        case 'F':
            return 5;
        default:
            return 8;
    }
}

static inline unsigned int is_leap(unsigned int year)
{
    return (year & 3) == 0 && (year % 100 != 0 || year % 400 == 0);
}

int meetup_day_of_month(unsigned int year,
                        unsigned int month,
                        const char *week,
                        const char *day_of_week)
{
    struct tm tm = {
        .tm_year = year - 1900,
        .tm_mon = month - 1,
        .tm_mday = 1
    };
    mktime(&tm);
    
    const int wday = weekday_to_num(day_of_week);
    if (wday > 7) return -1;

    int day = 1 + wday - tm.tm_wday;
    if (day <= 0) day += 7;

    const char week_first = week[0];
    const char week_second = week[1];
    
    switch (week_first) {
        case 'f':
            return day;
        case 's':
            return day + 7;
        case 't':
            return (week_second == 'h') ? day + 14 : 
                   ((day + 7) < 13 ? day + 14 : day + 7);
        case 'f' + 1:
            return day + 21;
        case 'l': {
            const int ndays = days_in_month[is_leap(year)][month - 1];
            return (day + 28) > ndays ? day + 21 : day + 28;
        }
        default:
            return -1;
    }
}