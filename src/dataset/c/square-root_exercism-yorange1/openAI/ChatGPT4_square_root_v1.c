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
        uint32_t square = (uint32_t)mid * mid;

        if (square == number)
        {
            return mid;
        }
        else if (square < number)
        {
            low = mid + 1;
            result = mid;
        }
        else
        {
            high = mid - 1;
        }
    }

    return result;
}