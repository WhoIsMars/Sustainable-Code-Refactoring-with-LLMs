#include "square_root.h"

#include <stdint.h>

uint16_t square_root(uint16_t number)
{
    if (number == 0)
    {
        return 0;
    }
    
    if (number == 1)
    {
        return 1;
    }
    
    uint16_t x = number;
    uint16_t prev;
    
    do {
        prev = x;
        x = (x + number / x) >> 1;
    } while (x < prev);
    
    return prev;
}