#include "time_v.h"
#include <stdio.h>   // For snprintf
#include <stddef.h>  // For NULL
#include <stdint.h>  // For integer types
#include <string.h>

/// Simulate system time (Unix timestamp: seconds since 1970-epoch)
static time_t system_time = 1700000000;  // Example timestamp

time_t time_v(time_t *t) {
    if (t != NULL) {
        *t = system_time;
    }
    return system_time;
}

tm_v *localtime_v(time_t *t) {
    static tm_v result;
    if (t == NULL) return NULL;

    time_t timestamp = *t;

    result.tm_sec  = timestamp % 60;
    result.tm_min  = (timestamp / 60) % 60;
    result.tm_hour = (timestamp / 3600) % 24;
    result.tm_mday = (timestamp / 86400) % 30 + 1;  // Fake 30-day months
    result.tm_mon  = (timestamp / (86400 * 30)) % 12;
    result.tm_year = 70 + (timestamp / (86400 * 365)); // Since 1970
    result.tm_wday = (timestamp / 86400) % 7;
    result.tm_yday = (timestamp / 86400) % 365;

    return &result;
}

int is_leap_year(int year){
    year += 1900;
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void normalize_tm_v(struct tm_v *tm){
//normalize seconds    
    while (tm->tm_sec >= 60){
        tm -> tm_sec -= 60;
        tm->tm_min++;
    }
    while (tm->tm_sec < 0){
        tm->tm_sec += 60;
        tm->tm_min--;
    }
//normalize minutes
    while (tm->tm_min >= 60){
        tm->tm_min -= 60;
        tm->tm_hour++;
    }
    while (tm->tm_min < 0){
        tm->tm_min += 60;
        tm->tm_hour--;
    }
//normalize hours
    while (tm->tm_hour >= 24){
        tm->tm_mday++;
        tm->tm_hour -= 24;
    }
    while (tm->tm_hour < 0){
        tm->tm_mday--;
        tm->tm_hour += 24;
    }

//normalize days of month
    while (tm->tm_mday >= days_in_month[tm->tm_mon]){
        tm->tm_mday -= days_in_month[tm->tm_mon];
        tm->tm_mon++;
    }
    while (tm->tm_mday < 0){
        tm->tm_mon--;
        tm->tm_mday += days_in_month[tm->tm_mon -1];//not sure and need to check
    }

//normalize months
    while (tm->tm_mon >= 12){
        tm->tm_year++;
        tm->tm_mon -= 12;
    }
    while (tm->tm_mon < 0){
        tm->tm_year--;
        tm->tm_mon += 12;
    }



    
}


time_t mktime_v(struct tm_v *tm) {
    if (tm == NULL) return 0;



    time_t timestamp = 0;
    timestamp += tm->tm_sec;
    timestamp += tm->tm_min * 60;
    timestamp += tm->tm_hour * 3600;
    timestamp += (tm->tm_mday - 1) * 86400;
    timestamp += tm->tm_mon * (86400 * 30);
    timestamp += (tm->tm_year - 70) * (86400 * 365);

    return timestamp;
}


size_t strftime_v(char *s, size_t max, const char *format, struct tm_v *tm) {
    if (!s || !format || !tm) return 0;  // Invalid input

    char buffer[256];  // Temporary buffer
    char *out = buffer;
    const char *ptr = format;
    size_t len = 0;

    while (*ptr && len < max - 1) {
        if (*ptr == '%') {
            ptr++;  // Move past '%'
            char temp[32] = {0};  // Store formatted value
            switch (*ptr) {
                case 'Y': snprintf(temp, sizeof(temp), "%04d", tm->tm_year + 1900); break;
                case 'm': snprintf(temp, sizeof(temp), "%02d", tm->tm_mon + 1); break;
                case 'd': snprintf(temp, sizeof(temp), "%02d", tm->tm_mday); break;
                case 'H': snprintf(temp, sizeof(temp), "%02d", tm->tm_hour); break;
                case 'M': snprintf(temp, sizeof(temp), "%02d", tm->tm_min); break;
                case 'S': snprintf(temp, sizeof(temp), "%02d", tm->tm_sec); break;
                default:  snprintf(temp, sizeof(temp), "%%%c", *ptr); break;  // Unsupported format
            }
            size_t temp_len = strlen(temp);
            if (len + temp_len < max - 1) {
                strcpy(out, temp);
                out += temp_len;
                len += temp_len;
            }
        } else {
            *out++ = *ptr;
            len++;
        }
        ptr++;
    }

    *out = '\0';  // Null-terminate the string
    strncpy(s, buffer, max);
    return len;
}

char *strptime_v(const char *s, const char *format,struct tm_v *tm) {
    if (!s || !format || !tm) return NULL;  // Invalid input

    const char *p = s;
    const char *f = format;

    while (*f && *p) {
        if (*f == '%') {
            f++;  // Move past '%'
            int value = 0;
           

            switch (*f) {
                case 'Y':  // Year (4 digits)
                    if (sscanf(p, "%4d", &value) == 1) {
                        tm->tm_year = value - 1900;
                        p += 4;
                    } else {
                        return NULL;
                    }
                    break;
                case 'm':  // Month (01-12)
                    if (sscanf(p, "%2d", &value) == 1) {
                        tm->tm_mon = value - 1;
                        p += 2;
                    } else {
                        return NULL;
                    }
                    break;
                case 'd':  // Day (01-31)
                    if (sscanf(p, "%2d", &value) == 1) {
                        tm->tm_mday = value;
                        p += 2;
                    } else {
                        return NULL;
                    }
                    break;
                case 'H':  // Hour (00-23)
                    if (sscanf(p, "%2d", &value) == 1) {
                        tm->tm_hour = value;
                        p += 2;
                    } else {
                        return NULL;
                    }
                    break;
                case 'M':  // Minute (00-59)
                    if (sscanf(p, "%2d", &value) == 1) {
                        tm->tm_min = value;
                        p += 2;
                    } else {
                        return NULL;
                    }
                    break;
                case 'S':  // Second (00-59)
                    if (sscanf(p, "%2d", &value) == 1) {
                        tm->tm_sec = value;
                        p += 2;
                    } else {
                        return NULL;
                    }
                    break;
                default:
                    return NULL;  // Unsupported format
            }
        } else if (*f == *p) {
            p++;  // Match literal character
        } else {
            return NULL;  // Mismatch
        }
        f++;
    }

    return (char *)p;  // Return pointer to next character in `s`
}




