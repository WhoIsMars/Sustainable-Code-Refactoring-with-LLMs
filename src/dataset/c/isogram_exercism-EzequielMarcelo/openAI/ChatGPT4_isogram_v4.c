#include "isogram.h"
#include <ctype.h>

bool is_isogram(const char phrase[]) 
{
    if (!phrase) 
        return false;

    unsigned int seen = 0;

    for (; *phrase; ++phrase) 
    {
        if (isalpha(*phrase)) 
        {
            unsigned int mask = 1U << (tolower(*phrase) - 'a');
            if (seen & mask) 
                return false;
            seen |= mask;
        }
    }

    return true;
}