#include "clock.h"

clock_t clock_create(int hour, int minute)
{
    clock_t clock;
    hour = (hour % 24 + 24) % 24; // Normalize hour to 0-23
    minute = (minute % 60 + 60) % 60; // Normalize minute to 0-59
    snprintf(clock.text, sizeof(clock.text), "%02d:%02d", hour, minute);
    return clock;
}

clock_t clock_add(clock_t clock, int minute_add)
{
    int hour, minute;
    sscanf(clock.text, "%d:%d", &hour, &minute);
    int total_minutes = hour * 60 + minute + minute_add;
    total_minutes = (total_minutes % 1440 + 1440) % 1440; // Normalize to 0-1439
    hour = total_minutes / 60;
    minute = total_minutes % 60;
    snprintf(clock.text, sizeof(clock.text), "%02d:%02d", hour, minute);
    return clock;
}

clock_t clock_subtract(clock_t clock, int minute_subtract)
{
    return clock_add(clock, -minute_subtract); // Reuse clock_add for subtraction
}

bool clock_is_equal(clock_t a, clock_t b)
{
    return strcmp(a.text, b.text) == 0; // Compare strings directly
}