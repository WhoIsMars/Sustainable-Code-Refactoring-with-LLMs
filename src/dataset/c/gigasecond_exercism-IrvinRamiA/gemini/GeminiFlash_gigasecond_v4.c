#include "gigasecond.h"
#include <stdint.h>

time_t gigasecond_after(time_t time)
{
    return time + INT64_C(1000000000);
}