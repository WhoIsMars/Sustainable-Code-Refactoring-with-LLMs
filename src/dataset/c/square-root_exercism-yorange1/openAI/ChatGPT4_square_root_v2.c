#include "square_root.h"

#include <math.h>

uint16_t square_root(uint16_t number)
{
    if (number == 0 || number == 1)
    {
        return number;
    }

    uint16_t low = 1, high = number, result = 0;

    while (low <= high)
    {
        uint16_t mid = low + (high - low) / 2;

        if (mid <= number / mid)
        {
            result = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return result;
}