#include "meetup.h"
#include <time.h>
#include <string.h>

static const char weekdays[] = "SundayMondayTuesdayWednesdayThursdayFridaySaturday";
static const unsigned char weekday_offsets[] = {0, 6, 12, 19, 28, 36, 42, 48};
static const unsigned char days_in_month[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

static unsigned int weekday_to_num(const char *weekday)
{
    char first_char = weekday[0];
    char second_char = weekday[1];
    
    switch (first_char) {
        case 'S':
            return (second_char == 'u') ? 0 : 6; // Sunday or Saturday
        case 'M': return 1; // Monday
        case 'T':
            return (second_char == 'u') ? 2 : 4; // Tuesday or Thursday
        case 'W': return 3; // Wednesday
        case 'F': return 5; // Friday
        default: return 8;
    }
}

static inline unsigned int is_leap(unsigned int year)
{
    return !(year & 3) && ((year % 100) || !(year % 400));
}

int meetup_day_of_month(unsigned int year,
                        unsigned int month,
                        const char *week,
                        const char *day_of_week)
{
    struct tm tm = {
        .tm_year = year - 1900,
        .tm_mon = month - 1,
        .tm_mday = 1,
    };
    mktime(&tm);
    
    int wday = weekday_to_num(day_of_week);
    if (wday > 7)
        return -1;

    int day = 1 + wday - tm.tm_wday;
    if (day <= 0)
        day += 7;

    char week_first = week[0];
    switch (week_first) {
        case 'f': // first
            return day;
        case 's': // second
            return day + 7;
        case 't':
            if (week[1] == 'h') // third
                return day + 14;
            else // teenth
                return (day + 7) < 13 ? day + 14 : day + 7;
        case 'f': // fourth (handled above as first, need different approach)
            if (week[1] == 'o') // fourth
                return day + 21;
            return day; // first (fallback)
        case 'l': // last
            {
                int ndays = days_in_month[is_leap(year)][month - 1];
                return (day + 28) > ndays ? day + 21 : day + 28;
            }
        default:
            if (week[1] == 'o') // fourth
                return day + 21;
            return -1;
    }
}