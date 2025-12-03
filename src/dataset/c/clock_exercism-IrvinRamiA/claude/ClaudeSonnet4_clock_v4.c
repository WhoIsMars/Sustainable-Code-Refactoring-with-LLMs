#include "clock.h"

clock_t clock_create(int hour, int minute)
{
    clock_t clock;
    hour %= 24;
    minute %= 60;
    if (hour < 0) hour += 24;
    if (minute < 0) minute += 60;
    
    clock.text[0] = '0' + (hour / 10);
    clock.text[1] = '0' + (hour % 10);
    clock.text[2] = ':';
    clock.text[3] = '0' + (minute / 10);
    clock.text[4] = '0' + (minute % 10);
    clock.text[5] = '\0';
    
    return clock;
}

clock_t clock_add(clock_t clock, int minute_add)
{
    int hour = (clock.text[0] - '0') * 10 + (clock.text[1] - '0');
    int minute = (clock.text[3] - '0') * 10 + (clock.text[4] - '0');
    
    minute += minute_add;
    hour += minute / 60;
    minute %= 60;
    hour %= 24;
    
    if (minute < 0) {
        minute += 60;
        hour--;
    }
    if (hour < 0) {
        hour += 24;
    }
    
    return clock_create(hour, minute);
}

clock_t clock_subtract(clock_t clock, int minute_subtract)
{
    return clock_add(clock, -minute_subtract);
}

bool clock_is_equal(clock_t a, clock_t b)
{
    return a.text[0] == b.text[0] && 
           a.text[1] == b.text[1] && 
           a.text[3] == b.text[3] && 
           a.text[4] == b.text[4];
}