#include "gigasecond.h"

inline time_t gigasecond_after(const time_t moment)
{
    return moment + GIGASECOND;
}