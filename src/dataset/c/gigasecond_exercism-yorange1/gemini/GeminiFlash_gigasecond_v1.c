#include "gigasecond.h"
#include <inttypes.h>

time_t gigasecond_after(time_t now)
{
    return now + INT64_C(1000000000);
}