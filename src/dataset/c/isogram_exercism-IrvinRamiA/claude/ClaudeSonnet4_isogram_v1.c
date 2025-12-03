#include "isogram.h"
#include <string.h>
#include <stdint.h>
#include <ctype.h>

bool is_isogram(const char phrase[])
{
    if (phrase == NULL)
    {
        return false;
    }

    uint32_t seen = 0;
    
    for (const char *p = phrase; *p; p++)
    {
        if (isalpha(*p))
        {
            uint8_t bit_pos = tolower(*p) - 'a';
            uint32_t mask = 1U << bit_pos;
            
            if (seen & mask)
            {
                return false;
            }
            
            seen |= mask;
        }
    }

    return true;
}