#include "isogram.h"
#include <stdio.h>
#include <ctype.h>

bool is_isogram(const char phrase[])
{
    if(phrase == NULL)
        return false;
    
    unsigned int seen = 0;
    
    for (const char *p = phrase; *p; ++p)
    {
        if (isalpha(*p))
        {
            unsigned int bit = 1u << (tolower(*p) - 'a');
            if (seen & bit)
                return false;
            seen |= bit;
        }
    }
    return true;
}