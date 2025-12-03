#include "square_root.h"

unsigned char square_root(unsigned short number)
{
    if (number == 0) return 0;

    unsigned char low = 1;
    unsigned char high = (number < 256) ? number : 255; // Optimization: Limit high to 255

    while (low <= high) {
        unsigned char mid = low + (high - low) / 2; // Prevent potential overflow
        unsigned short square = (unsigned short)mid * mid; // Cast to prevent overflow during multiplication

        if (square == number) {
            return mid;
        } else if (square < number) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return low;
}