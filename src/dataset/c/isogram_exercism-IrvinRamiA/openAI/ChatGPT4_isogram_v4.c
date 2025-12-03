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

    bool char_seen[26] = {false};
    for (uint8_t i = 0; phrase[i] != '\0'; i++)
    {
        if (isalpha(phrase[i]))
        {
            uint8_t index = tolower(phrase[i]) - 'a';
            if (char_seen[index])
            {
                return false;
            }
            char_seen[index] = true;
        }
    }

    return true;
}