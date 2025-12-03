#include "square_root.h"

unsigned char square_root(unsigned short number)
{
    if (number == 0) return 0;
    if (number <= 3) return 1;
    
    unsigned char left = 1;
    unsigned char right = (number > 255) ? 255 : (unsigned char)number;
    unsigned char result = 1;
    
    while (left <= right) {
        unsigned char mid = left + ((right - left) >> 1);
        unsigned short square = (unsigned short)mid * mid;
        
        if (square == number) {
            return mid;
        } else if (square < number) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}