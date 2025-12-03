#include "square_root.h"

#include <stdint.h>

uint16_t square_root(uint16_t number)
{
    if (number == 0)
        return 0;
    
    if (number == 1)
        return 1;
    
    uint32_t x = number;
    uint32_t y = (x + 1) >> 1;
    
    while (y < x) {
        x = y;
        y = (x + number / x) >> 1;
    }
    
    return (uint16_t)x;
}