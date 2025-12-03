#include "clock.h"

clock_t clock_create(int hour, int minute)
{
    clock_t clock;
    hour %= 24;
    minute %= 60;
    
    clock.hour = hour;
    clock.minute = minute;
    
    if (hour < 10) {
        if (minute < 10) {
            clock.text[0] = '0';
            clock.text[1] = '0' + hour;
            clock.text[2] = ':';
            clock.text[3] = '0';
            clock.text[4] = '0' + minute;
            clock.text[5] = '\0';
        } else {
            clock.text[0] = '0';
            clock.text[1] = '0' + hour;
            clock.text[2] = ':';
            clock.text[3] = '0' + (minute / 10);
            clock.text[4] = '0' + (minute % 10);
            clock.text[5] = '\0';
        }
    } else {
        if (minute < 10) {
            clock.text[0] = '0' + (hour / 10);
            clock.text[1] = '0' + (hour % 10);
            clock.text[2] = ':';
            clock.text[3] = '0';
            clock.text[4] = '0' + minute;
            clock.text[5] = '\0';
        } else {
            clock.text[0] = '0' + (hour / 10);
            clock.text[1] = '0' + (hour % 10);
            clock.text[2] = ':';
            clock.text[3] = '0' + (minute / 10);
            clock.text[4] = '0' + (minute % 10);
            clock.text[5] = '\0';
        }
    }
    
    return clock;
}

clock_t clock_add(clock_t clock, int minute_add)
{
    int total_minutes = clock.hour * 60 + clock.minute + minute_add;
    total_minutes = ((total_minutes % 1440) + 1440) % 1440;
    
    return clock_create(total_minutes / 60, total_minutes % 60);
}

clock_t clock_subtract(clock_t clock, int minute_subtract)
{
    return clock_add(clock, -minute_subtract);
}

bool clock_is_equal(clock_t a, clock_t b)
{
    return a.hour == b.hour && a.minute == b.minute;
}