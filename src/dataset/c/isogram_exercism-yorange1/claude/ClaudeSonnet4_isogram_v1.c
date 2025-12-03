#include "isogram.h"

#include <stddef.h>
#include <stdint.h>
#include <ctype.h>

bool is_isogram(const char phrase[])
{
    if (NULL == phrase)
    {
        return false;
    }

    uint32_t flags = 0;
    
    for (const char *p = phrase; *p; p++)
    {
        if (isalpha(*p))
        {
            uint32_t bit = 1U << ((*p | 0x20) - 'a');
            if (flags & bit)
            {
                return false;
            }
            flags |= bit;
        }
    }

    return true;
}