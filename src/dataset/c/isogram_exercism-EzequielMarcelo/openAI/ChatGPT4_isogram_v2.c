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
            char c = tolower(*p) - 'a';
            unsigned int mask = 1U << c;

            if (seen & mask) 
                return false;

            seen |= mask;
        }
    }

    return true;
}