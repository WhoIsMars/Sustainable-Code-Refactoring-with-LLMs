#include "square_root.h"

unsigned int square_root(unsigned int number)
{
    if (number == 0) return 0;

    unsigned int low = 1, high = number;
    unsigned int result = 0;

    while (low <= high) {
        unsigned int mid = low + (high - low) / 2;
        unsigned int sq = number / mid;

        if (sq == mid) {
            if (number % mid == 0)
                return mid;
            else
                high = mid - 1;
        }
        else if (sq < mid) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
            result = mid;
        }
    }
    
    unsigned int res_sq = result * result;
    if (res_sq == number)
        return result;
    
    return -1;
}