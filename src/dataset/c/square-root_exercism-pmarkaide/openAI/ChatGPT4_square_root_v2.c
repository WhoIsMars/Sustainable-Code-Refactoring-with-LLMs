#include "square_root.h"

unsigned int square_root(unsigned int number)
{
    if (number == 0 || number == 1)
        return number;

    unsigned int start = 0, end = number, result = 0;

    while (start <= end)
    {
        unsigned int mid = start + (end - start) / 2;

        if (mid * mid == number)
            return mid;

        if (mid * mid < number)
        {
            start = mid + 1;
            result = mid;
        }
        else
        {
            end = mid - 1;
        }
    }
    return result;
}