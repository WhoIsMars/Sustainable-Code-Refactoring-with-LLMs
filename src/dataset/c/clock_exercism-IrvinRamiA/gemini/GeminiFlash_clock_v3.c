#include "clock.h"
#include <stdio.h>
#include <stdbool.h>

clock_t clock_create(int hour, int minute)
{
    clock_t clock;
    clock.hour = hour;
    clock.minute = minute;
    snprintf(clock.text, sizeof(clock.text), "%02d:%02d", hour, minute);
    return clock;
}

clock_t clock_add(clock_t clock, int minute_add)
{
    int total_minutes = clock.minute + minute_add;
    int new_minute = total_minutes % 60;
    int hour_add = total_minutes / 60;
    int new_hour = (clock.hour + hour_add) % 24;

    clock_t new_clock = clock_create(new_hour, new_minute);
    return new_clock;
}

clock_t clock_subtract(clock_t clock, int minute_subtract)
{
    int total_minutes = clock.minute - minute_subtract;
    int new_hour = clock.hour;

    while (total_minutes < 0) {
        total_minutes += 60;
        new_hour = (new_hour + 24 - 1) % 24;
    }

    int new_minute = total_minutes % 60;

    clock_t new_clock = clock_create(new_hour, new_minute);
    return new_clock;
}

bool clock_is_equal(clock_t a, clock_t b)
{
    return (a.hour == b.hour && a.minute == b.minute);
}