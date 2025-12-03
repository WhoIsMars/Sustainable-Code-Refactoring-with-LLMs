#include "isogram.h"

#include <stddef.h>
#include <stdint.h>
#include <ctype.h>

bool is_isogram(const char phrase[])
{
    if (!phrase)
    {
        return false;
    }

    uint32_t flags = 0;

    for (const char *p = phrase; *p; ++p)
    {
        if (isalpha(*p))
        {
            size_t index = tolower(*p) - 'a';
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