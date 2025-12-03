#include "gigasecond.h"

inline time_t gigasecond_after(time_t now)
{
    return now + 1000000000;
}