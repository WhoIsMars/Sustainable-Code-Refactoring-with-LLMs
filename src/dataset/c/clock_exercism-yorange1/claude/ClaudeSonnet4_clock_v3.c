#include "clock.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MINUTE_PER_HOUR (60)
#define HOUR_PER_DAY (24)
#define MINUTE_PER_DAY (1440)

static inline int normalize_minutes(int total_minute)
{
    if (total_minute >= 0) {
        return total_minute % MINUTE_PER_DAY;
    }
    
    int remainder = total_minute % MINUTE_PER_DAY;
    return remainder == 0 ? 0 : remainder + MINUTE_PER_DAY;
}

static clock_t minute_to_clock(int total_minute)
{
    total_minute = normalize_minutes(total_minute);
    
    int actual_hour = total_minute / MINUTE_PER_HOUR;
    int actual_minute = total_minute % MINUTE_PER_HOUR;

    clock_t clock;
    snprintf(clock.text, MAX_STR_LEN, "%02d:%02d", actual_hour, actual_minute);

    return clock;
}

clock_t clock_create(int hour, int minute)
{
    int total_minute = hour * MINUTE_PER_HOUR + minute;
    return minute_to_clock(total_minute);
}

clock_t clock_add(clock_t clock, int minute_add)
{
    int clock_hour = (clock.text[0] - '0') * 10 + (clock.text[1] - '0');
    int clock_minute = (clock.text[3] - '0') * 10 + (clock.text[4] - '0');
    
    int total_minute = clock_hour * MINUTE_PER_HOUR + clock_minute + minute_add;
    return minute_to_clock(total_minute);
}

clock_t clock_subtract(clock_t clock, int minute_subtract)
{
    int clock_hour = (clock.text[0] - '0') * 10 + (clock.text[1] - '0');
    int clock_minute = (clock.text[3] - '0') * 10 + (clock.text[4] - '0');
    
    int total_minute = clock_hour * MINUTE_PER_HOUR + clock_minute - minute_subtract;
    return minute_to_clock(total_minute);
}

bool clock_is_equal(clock_t a, clock_t b)
{
    return (a.text[0] == b.text[0] && a.text[1] == b.text[1] && 
            a.text[3] == b.text[3] && a.text[4] == b.text[4]);
}