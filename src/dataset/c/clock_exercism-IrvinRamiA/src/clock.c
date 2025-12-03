#include "clock.h"

clock_t clock_create(int hour, int minute)
{
    clock_t clock;
    if (hour < 10 && minute < 10)
    {
        sprintf(clock.text, "0%d:0%d", hour, minute);
    }

    return clock;
}

clock_t clock_add(clock_t clock, int minute_add)
{

}

clock_t clock_subtract(clock_t clock, int minute_subtract)
{

}

bool clock_is_equal(clock_t a, clock_t b)
{

}
