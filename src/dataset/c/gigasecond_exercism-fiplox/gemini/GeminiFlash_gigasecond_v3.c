#include "gigasecond.h"
#include <time.h>

time_t gigasecond_after(time_t moment)
{
    return moment + GIGASECOND;
}