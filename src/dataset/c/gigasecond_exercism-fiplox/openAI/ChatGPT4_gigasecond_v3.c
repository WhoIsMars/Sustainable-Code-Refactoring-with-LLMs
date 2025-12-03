#include "gigasecond.h"

inline time_t gigasecond_after(time_t moment)
{
    return moment + GIGASECOND;
}