#include "isogram.h"
#include <ctype.h>

bool is_isogram(const char phrase[]) 
{
    if (!phrase) 
        return false;

    unsigned int seen = 0;

    for (const char *p = phrase; *p; ++p) 
    {
        if (isalpha(*p)) 
        {
            unsigned int mask = 1u << (tolower(*p) - 'a');
            if (seen & mask) 
                return false;
            seen |= mask;
        }
    }

    return true;
}