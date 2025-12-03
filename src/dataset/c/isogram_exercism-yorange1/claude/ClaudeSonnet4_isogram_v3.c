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
    const char *ptr = phrase;
    
    while (*ptr)
    {
        if (isalpha(*ptr))
        {
            uint32_t bit = 1U << ((*ptr | 0x20) - 'a');
            if (flags & bit)
            {
                return false;
            }
            flags |= bit;
        }
        ptr++;
    }

    return true;
}