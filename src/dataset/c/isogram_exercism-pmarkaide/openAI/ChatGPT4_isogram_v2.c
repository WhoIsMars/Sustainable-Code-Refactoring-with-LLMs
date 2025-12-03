#include "isogram.h"
#include <ctype.h>

bool is_isogram(const char phrase[])
{
    if (!phrase)
        return false;

    unsigned int checker = 0; // bit vector for 26 letters
    for (int i = 0; phrase[i] != '\0'; i++)
    {
        if (isalpha(phrase[i]))
        {
            int bit = tolower(phrase[i]) - 'a';
            if (checker & (1 << bit))
                return false;
            checker |= (1 << bit);
        }
    }
    return true;
}