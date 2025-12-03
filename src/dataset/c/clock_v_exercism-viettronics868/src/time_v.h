#ifndef TIME_V_H
#define TIME_V_H

#include <stddef.h>  // For size_t

        
// Define our own time_t (typically an integer type)
typedef unsigned long long time_t;

// Define struct tm_v (equivalent to struct tm)
typedef struct tm_v {  //struct tag is tm_v
    int tm_sec;    // seconds [0, 59]
    
    int tm_min;    // minutes [0, 59]
    int tm_hour;   // hours [0, 23]
    int tm_mday;   // day of the month [1, 31]
    int tm_mon;    // months since January [0, 11]
    int tm_year;   // years since 1900
    int tm_wday;   // days since Sunday [0, 6]
    int tm_yday;   // days since January 1 [0, 365]
    int tm_isdst;  // daylight saving time flag
} tm_v; 

static const int days_in_month[]        = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static const int days_in_month_leap[]   = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

time_t time_v(time_t *t);
tm_v *localtime_v( time_t *t);
time_t mktime_v(struct tm_v *tm);
size_t strftime_v(char *s, size_t max, const char *format, struct tm_v *tm);
char *strptime_v(const char *s, const char *format, struct tm_v *tm);

#endif // TIME_V_H
