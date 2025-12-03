#include "pangram.h"
#include <stdlib.h>
#include <stdio.h>

bool is_pangram(const char *sentence)
{
    bool result = true;
    bool *checkbox_alphabet = (bool *)calloc(26, sizeof(bool));

    if (sentence == NULL)
    {
        result = false;
    }
    else
    {
        while (*sentence != '\0')
        {
            if(*sentence >= 'A' && *sentence <= 'Z')
            {
                checkbox_alphabet[*(sentence) - 'A'] = true;
            }
            else if (*sentence >= 'a' && *sentence <= 'z')
            {
                checkbox_alphabet[*(sentence) - 'a'] = true;
            }
            sentence++;
        }

        for (unsigned char i = 0; i < 26; i++)
        {
            if (*(checkbox_alphabet + i) != true)
            {
                result = false;
                break;
            }
        }
    }

    return result;
}

/**
 * "abcdefghijklmnopqrstuvwxyz"
 * 'a' -> 97
 * 'z' -> 122
 * 'A' -> 65
 * 'Z' -> 90
 */
