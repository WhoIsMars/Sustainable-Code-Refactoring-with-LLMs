#include "isogram.h"
#include <stdint.h>

bool is_isogram(const char phrase[])
{
    if(phrase == NULL)
        return false;
    
    uint32_t seen = 0;
    
    for (const char *p = phrase; *p; p++)
    {
        if ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z'))
        {
            int bit_pos = (*p | 32) - 'a';
            if (seen & (1U << bit_pos))
                return false;
            seen |= (1U << bit_pos);
        }
    }
    return true;
}