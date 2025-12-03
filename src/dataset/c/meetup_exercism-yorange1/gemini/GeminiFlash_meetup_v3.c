#include "meetup.h"
#include <time.h>
#include <string.h>

static const char *weekdays[] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

static const unsigned int days_in_month[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

static unsigned int weekday_to_num(const char *weekday) {
    for (unsigned int i = 0; i < 7; ++i) {
        if (weekday[0] == weekdays[i][0] && strcmp(weekdays[i], weekday) == 0) {
            return i;
        }
    }
    return 8;
}

static unsigned int is_leap(unsigned int year) {
    return (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
}

int meetup_day_of_month(unsigned int year,
                        unsigned int month,
                        const char *week,
                        const char *day_of_week) {
    int wday = weekday_to_num(day_of_week);
    if (wday > 7) {
        return -1;
    }

    int first_day_of_month;
    {
        struct tm tm = {
            .tm_year = (int)year - 1900,
            .tm_mon = (int)month - 1,
            .tm_mday = 1,
            .tm_hour = 12 // Set to noon to avoid DST issues
        };
        time_t t = mktime(&tm);
        if (t == -1) return -1; // Handle potential mktime failure
        struct tm tm_result = *localtime(&t); // Use localtime for correct weekday
        first_day_of_month = tm_result.tm_wday;
    }

    int day = 1 + wday - first_day_of_month;
    if (day <= 0) {
        day += 7;
    }

    int result = -1;

    if (week[0] == 'f' && strcmp(week, "first") == 0) {
        result = day;
    } else if (week[0] == 's' && strcmp(week, "second") == 0) {
        result = day + 7;
    } else if (week[0] == 't') {
        if (week[2] == 'i' && strcmp(week, "third") == 0) {
            result = day + 14;
        } else if (week[2] == 'u' && strcmp(week, "fourth") == 0) {
            result = day + 21;
        } else if (week[1] == 'e' && strcmp(week, "teenth") == 0) {
            result = (day + 7) < 13 ? day + 14 : day + 7;
        }
    } else if (week[0] == 'l' && strcmp(week, "last") == 0) {
        int ndays = days_in_month[is_leap(year)][month - 1];
        result = (day + 28) > ndays ? day + 21 : day + 28;
    }

    return result;
}