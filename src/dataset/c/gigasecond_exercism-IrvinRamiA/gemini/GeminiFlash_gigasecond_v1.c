#include "gigasecond.h"
#include <math.h>

time_t gigasecond_after(time_t time)
{
    return time + (time_t)1e9;
}