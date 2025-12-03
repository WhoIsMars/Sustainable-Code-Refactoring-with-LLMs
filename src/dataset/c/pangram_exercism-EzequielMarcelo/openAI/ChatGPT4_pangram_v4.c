#include "pangram.h"
#include <stdint.h>
#include <ctype.h>

bool is_pangram(const char *sentence) 
{
    if (!sentence) 
        return false;

    uint32_t seen = 0;
    int count = 0;

    while (*sentence && count < ALPHABET_COUNT) 
    {
        char c = tolower(*sentence);
        if (c >= 'a' && c <= 'z') 
        {
            uint32_t mask = 1U << (c - 'a');
            if (!(seen & mask)) 
            {
                seen |= mask;
                count++;
            }
        }
        sentence++;
    }

    return count == ALPHABET_COUNT;
}