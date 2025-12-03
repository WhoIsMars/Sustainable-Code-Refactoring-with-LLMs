#include "clock.h"

clock_t clock_create(int hour, int minute)
{
    clock_t clock;
    
    // Normalize inputs to 24-hour format
    hour = ((hour % 24) + 24) % 24;
    minute = ((minute % 60) + 60) % 60;
    
    // Handle minute overflow
    if (minute >= 60) {
        hour = (hour + minute / 60) % 24;
        minute = minute % 60;
    }
    
    // Store as total minutes for efficient calculations
    clock.total_minutes = hour * 60 + minute;
    
    // Format string efficiently
    if (hour < 10) {
        if (minute < 10) {
            sprintf(clock.text, "0%d:0%d", hour, minute);
        } else {
            sprintf(clock.text, "0%d:%d", hour, minute);
        }
    } else {
        if (minute < 10) {
            sprintf(clock.text, "%d:0%d", hour, minute);
        } else {
            sprintf(clock.text, "%d:%d", hour, minute);
        }
    }
    
    return clock;
}

clock_t clock_add(clock_t clock, int minute_add)
{
    int total = clock.total_minutes + minute_add;
    total = ((total % 1440) + 1440) % 1440; // 1440 = 24 * 60
    
    int hour = total / 60;
    int minute = total % 60;
    
    return clock_create(hour, minute);
}

clock_t clock_subtract(clock_t clock, int minute_subtract)
{
    return clock_add(clock, -minute_subtract);
}

bool clock_is_equal(clock_t a, clock_t b)
{
    return a.total_minutes == b.total_minutes;
}