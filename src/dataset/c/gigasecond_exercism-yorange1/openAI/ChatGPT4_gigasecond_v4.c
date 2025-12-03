#include "gigasecond.h"

time_t gigasecond_after(const time_t now)
{
    return now + 1000000000L;
}