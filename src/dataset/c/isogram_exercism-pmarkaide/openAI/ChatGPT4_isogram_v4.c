#include "isogram.h"
#include <ctype.h>

bool is_isogram(const char phrase[])
{
    if (!phrase)
        return false;

    unsigned int seen = 0;

    for (int i = 0; phrase[i] != '\0'; i++)
    {
        if (isalpha(phrase[i]))
        {
            unsigned int mask = 1u << (tolower(phrase[i]) - 'a');
            if (seen & mask)
                return false;
            seen |= mask;
        }
    }
    return true;
}