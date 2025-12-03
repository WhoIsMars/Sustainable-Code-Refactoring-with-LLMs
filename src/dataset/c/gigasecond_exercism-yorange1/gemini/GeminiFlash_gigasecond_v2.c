#include "gigasecond.h"
#include <math.h>

time_t gigasecond_after(time_t now)
{
    return now + (time_t)1e9;
}