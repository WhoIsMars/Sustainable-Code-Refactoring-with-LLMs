#include "clock.h"
#include <stdio.h>
#include <stdbool.h>

#define MINUTES_IN_HOUR 60
#define HOURS_IN_DAY 24
#define MINUTES_IN_DAY (HOURS_IN_DAY * MINUTES_IN_HOUR)

clock_t clock_create(int hour, int minute)
{
    clock_t clock;
    hour = (hour % HOURS_IN_DAY + HOURS_IN_DAY) % HOURS_IN_DAY;
    minute = (minute % MINUTES_IN_DAY + MINUTES_IN_DAY) % MINUTES_IN_DAY;
    hour = (hour + minute / MINUTES_IN_HOUR) % HOURS_IN_DAY;
    minute %= MINUTES_IN_HOUR;
    snprintf(clock.text, sizeof(clock.text), "%02d:%02d", hour, minute);
    return clock;
}

clock_t clock_add(clock_t clock, int minute_add)
{
    int hour, minute;
    sscanf(clock.text, "%d:%d", &hour, &minute);
    int total_minutes = (hour * MINUTES_IN_HOUR + minute + minute_add) % MINUTES_IN_DAY;
    if (total_minutes < 0) total_minutes += MINUTES_IN_DAY;
    return clock_create(total_minutes / MINUTES_IN_HOUR, total_minutes % MINUTES_IN_HOUR);
}

clock_t clock_subtract(clock_t clock, int minute_subtract)
{
    return clock_add(clock, -minute_subtract);
}

bool clock_is_equal(clock_t a, clock_t b)
{
    return strncmp(a.text, b.text, sizeof(a.text)) == 0;
}