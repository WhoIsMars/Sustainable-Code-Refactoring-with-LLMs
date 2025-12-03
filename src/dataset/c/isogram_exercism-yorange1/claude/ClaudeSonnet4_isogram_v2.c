#include "isogram.h"

#include <stddef.h>
#include <stdint.h>

bool is_isogram(const char phrase[])
{
    if (NULL == phrase)
    {
        return false;
    }

    uint32_t flags = 0;

    for (const char *p = phrase; *p; p++)
    {
        char c = *p;
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            size_t index = (c & 0x1F) - 1;
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