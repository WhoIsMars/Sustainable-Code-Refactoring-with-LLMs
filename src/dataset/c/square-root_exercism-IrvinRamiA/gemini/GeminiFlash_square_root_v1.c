#include "square_root.h"

unsigned char square_root(unsigned short number)
{
    if (number == 0) return 0;

    unsigned char low = 1;
    unsigned char high = (number < 256) ? (unsigned char)number : 255;
    unsigned char result = 0;

    while (low <= high)
    {
        unsigned char mid = low + (high - low) / 2;
        unsigned short square = mid * mid;

        if (square == number)
        {
            return mid;
        }
        else if (square < number)
        {
            result = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return (unsigned char)((unsigned short)(result + 1) <= number / (result + 1) ? result + 1 : result);
}