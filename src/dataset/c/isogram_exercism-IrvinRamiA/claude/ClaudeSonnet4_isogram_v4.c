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
            int bit = tolower(*p) - 'a';
            if (seen & (1U << bit))
            {
                return false;
            }
            seen |= (1U << bit);
        }
    }

    return true;
}