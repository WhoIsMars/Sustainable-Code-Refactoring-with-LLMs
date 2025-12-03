#include "grains.h"
#include <math.h>

uint64_t square(uint8_t index)
{
    uint64_t result = 0;
    if(index > 0 && index < 65)
    {
        result = 1ull << (index - 1);
    }

    return result;
}

uint64_t total(void)
{
    uint64_t result = 0;
    for (uint8_t i = 1; i < 65; i++)
    {
        result += square(i);
    }

    return result;
}
