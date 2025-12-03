#include "pangram.h"
#include <stdbool.h>

bool is_pangram(const char *sentence)
{
    if (sentence == NULL)
    {
        return false;
    }

    unsigned int alphabet_mask = 0;
    while (*sentence)
    {
        if (*sentence >= 'A' && *sentence <= 'Z')
        {
            alphabet_mask |= 1 << (*sentence - 'A');
        }
        else if (*sentence >= 'a' && *sentence <= 'z')
        {
            alphabet_mask |= 1 << (*sentence - 'a');
        }
        if (alphabet_mask == 0x3FFFFFF) // All 26 bits set
        {
            return true;
        }
        sentence++;
    }

    return alphabet_mask == 0x3FFFFFF;
}