#include "clock.h"
#include <stdio.h>
#include <stdbool.h>

#define MINUTES_IN_HOUR 60
#define HOURS_IN_DAY 24
#define MINUTES_IN_DAY (HOURS_IN_DAY * MINUTES_IN_HOUR)

clock_t clock_create(int hour, int minute)
{
    clock_t clock;
    int total_minutes = ((hour % HOURS_IN_DAY) * MINUTES_IN_HOUR + (minute % MINUTES_IN_DAY) + MINUTES_IN_DAY) % MINUTES_IN_DAY;
    sprintf(clock.text, "%02d:%02d", total_minutes / MINUTES_IN_HOUR, total_minutes % MINUTES_IN_HOUR);
    return clock;
}

clock_t clock_add(clock_t clock, int minute_add)
{
    int hour, minute;
    sscanf(clock.text, "%d:%d", &hour, &minute);
    return clock_create(hour, minute + minute_add);
}

clock_t clock_subtract(clock_t clock, int minute_subtract)
{
    int hour, minute;
    sscanf(clock.text, "%d:%d", &hour, &minute);
    return clock_create(hour, minute - minute_subtract);
}

bool clock_is_equal(clock_t a, clock_t b)
{
    return strcmp(a.text, b.text) == 0;
}