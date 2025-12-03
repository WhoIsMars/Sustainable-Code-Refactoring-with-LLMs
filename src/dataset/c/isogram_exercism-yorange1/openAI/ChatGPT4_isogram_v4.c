#include "isogram.h"

#include <stddef.h>
#include <stdint.h>
#include <ctype.h>

bool is_isogram(const char phrase[])
{
    if (!phrase || !*phrase)
    {
        return true;
    }

    uint32_t flags = 0;

    for (const char *p = phrase; *p; ++p)
    {
        if (isalpha(*p))
        {
            uint32_t index = tolower(*p) - 'a';
            uint32_t mask = 1U << index;
            if (flags & mask)
            {
                return false;
            }
            flags |= mask;
        }
    }

    return true;
}