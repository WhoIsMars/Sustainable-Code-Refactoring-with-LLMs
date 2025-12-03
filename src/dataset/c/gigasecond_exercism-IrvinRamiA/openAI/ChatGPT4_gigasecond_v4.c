#include "gigasecond.h"

inline time_t gigasecond_after(time_t time)
{
    return time + 1000000000;
}