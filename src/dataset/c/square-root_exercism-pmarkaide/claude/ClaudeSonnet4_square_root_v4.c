#include "square_root.h"

unsigned int square_root(unsigned int number)
{
    if (number == 0 || number == 1)
        return number;
    
    unsigned int left = 1;
    unsigned int right = number;
    unsigned int result = 0;
    
    while (left <= right)
    {
        unsigned int mid = left + (right - left) / 2;
        
        if (mid <= number / mid)
        {
            result = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    
    return (result * result == number) ? result : (unsigned int)-1;
}