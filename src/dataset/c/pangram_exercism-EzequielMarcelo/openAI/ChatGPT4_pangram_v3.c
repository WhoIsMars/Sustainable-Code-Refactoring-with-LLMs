#include "pangram.h"
#include <stdint.h>

bool is_pangram(const char *sentence) 
{
    if (sentence == NULL) 
        return false; 

    uint32_t seen = 0;
    int required = (1 << ALPHABET_COUNT) - 1;

    for (; *sentence; sentence++) 
    {
        char c = tolower(*sentence);
        if (c >= 'a' && c <= 'z') 
        {
            seen |= 1 << (c - 'a');
            if (seen == required)
                return true;
        }
    }

    return false;
}