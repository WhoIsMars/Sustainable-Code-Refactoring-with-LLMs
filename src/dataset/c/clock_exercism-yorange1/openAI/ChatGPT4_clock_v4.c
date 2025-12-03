#include "clock.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MINUTE_PER_HOUR 60
#define HOUR_PER_DAY 24
#define MINUTE_PER_DAY (MINUTE_PER_HOUR * HOUR_PER_DAY)

static clock_t minute_to_clock(int total_minute)
{
    total_minute = ((total_minute % MINUTE_PER_DAY) + MINUTE_PER_DAY) % MINUTE_PER_DAY;

    clock_t clock;
    snprintf(clock.text, MAX_STR_LEN, "%02d:%02d", total_minute / MINUTE_PER_HOUR, total_minute % MINUTE_PER_HOUR);

    return clock;
}

clock_t clock_create(int hour, int minute)
{
    return minute_to_clock(hour * MINUTE_PER_HOUR + minute);
}

clock_t clock_add(clock_t clock, int minute_add)
{
    int clock_hour, clock_minute;
    sscanf(clock.text, "%2d:%2d", &clock_hour, &clock_minute);

    return minute_to_clock(clock_hour * MINUTE_PER_HOUR + clock_minute + minute_add);
}

clock_t clock_subtract(clock_t clock, int minute_subtract)
{
    int clock_hour, clock_minute;
    sscanf(clock.text, "%2d:%2d", &clock_hour, &clock_minute);

    return minute_to_clock(clock_hour * MINUTE_PER_HOUR + clock_minute - minute_subtract);
}

bool clock_is_equal(clock_t a, clock_t b)
{
    return strcmp(a.text, b.text) == 0;
}