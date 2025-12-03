#include "isogram.h"
#include <ctype.h>

bool is_isogram(const char phrase[])
{
    if (!phrase)
        return false;

    unsigned int seen = 0; // bitmask to track letters

    for (int i = 0; phrase[i] != '\0'; i++)
    {
        if (isalpha(phrase[i]))
        {
            int bit = 1 << (tolower(phrase[i]) - 'a');
            if (seen & bit)
                return false;
            seen |= bit;
        }
    }
    return true;
}