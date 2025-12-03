#include "square_root.h"

unsigned char square_root(unsigned short number)
{
    if (number == 0) return 0;
    if (number <= 3) return 1;
    
    unsigned char low = 1;
    unsigned char high = (number > 255) ? 255 : (unsigned char)number;
    unsigned char result = 1;
    
    while (low <= high) {
        unsigned char mid = low + ((high - low) >> 1);
        unsigned short square = (unsigned short)mid * mid;
        
        if (square == number) {
            return mid;
        } else if (square < number) {
            result = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    return result;
}