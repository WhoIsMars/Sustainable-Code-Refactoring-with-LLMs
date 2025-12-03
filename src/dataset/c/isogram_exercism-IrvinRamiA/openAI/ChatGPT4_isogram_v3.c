#include "isogram.h"
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>

bool is_isogram(const char phrase[])
{
    if (phrase == NULL)
    {
        return false;
    }

    bool seen[26] = {false};
    for (const char *ptr = phrase; *ptr != '\0'; ++ptr)
    {
        if (isalpha(*ptr))
        {
            uint8_t index = tolower(*ptr) - 'a';
            if (seen[index])
            {
                return false;
            }
            seen[index] = true;
        }
    }

    return true;
}