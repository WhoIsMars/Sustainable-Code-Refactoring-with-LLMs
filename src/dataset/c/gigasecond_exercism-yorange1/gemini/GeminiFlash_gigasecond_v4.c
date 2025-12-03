#include "gigasecond.h"
#include <stdint.h>

time_t gigasecond_after(time_t now)
{
    return now + (time_t)1000000000;
}