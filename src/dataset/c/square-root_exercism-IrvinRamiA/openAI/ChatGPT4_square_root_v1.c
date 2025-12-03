#include "square_root.h"

unsigned char square_root(unsigned short number)
{
    unsigned char low = 1, high = number < 255 ? number : 255, mid;

    while (low <= high)
    {
        mid = (low + high) / 2;
        unsigned short mid_squared = mid * mid;

        if (mid_squared == number)
            return mid;
        else if (mid_squared < number)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return high;
}