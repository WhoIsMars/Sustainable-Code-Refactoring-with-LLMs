#include "square_root.h"

unsigned char square_root(unsigned short number)
{
    if (number == 0 || number == 1)
        return number;

    unsigned char low = 1, high = number < 255 ? number : 255, result = 1;

    while (low <= high)
    {
        unsigned char mid = low + (high - low) / 2;

        if (mid * mid == number)
            return mid;
        else if (mid * mid < number)
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