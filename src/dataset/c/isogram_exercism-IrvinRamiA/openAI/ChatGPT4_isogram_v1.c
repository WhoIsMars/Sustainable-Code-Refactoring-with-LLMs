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

    bool seen[26] = {false}; // Array to track seen letters (case insensitive)

    for (uint8_t i = 0; phrase[i] != '\0'; i++)
    {
        if (isalpha(phrase[i]))
        {
            uint8_t index = tolower(phrase[i]) - 'a';
            if (seen[index]) // If letter already seen, it's not an isogram
            {
                return false;
            }
            seen[index] = true; // Mark letter as seen
        }
    }

    return true;
}