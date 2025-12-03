/**
 * @file raindrops.c
 * @brief If input is a number return the number as character,
 * if multiple of 3 => return Pling
 * if multiple of 5 => return Plang
 * if multiple of 7 => return Plong
 */

#include "raindrops.h"
#include <stdio.h>

const char *convert(char result[], int drops)
{
    char *ptr = result;
    int has_sound = 0;
    
    if (drops % 3 == 0)
    {
        *ptr++ = 'P'; *ptr++ = 'l'; *ptr++ = 'i'; *ptr++ = 'n'; *ptr++ = 'g';
        has_sound = 1;
    }
    if (drops % 5 == 0)
    {
        *ptr++ = 'P'; *ptr++ = 'l'; *ptr++ = 'a'; *ptr++ = 'n'; *ptr++ = 'g';
        has_sound = 1;
    }
    if (drops % 7 == 0)
    {
        *ptr++ = 'P'; *ptr++ = 'l'; *ptr++ = 'o'; *ptr++ = 'n'; *ptr++ = 'g';
        has_sound = 1;
    }
    
    if (!has_sound)
    {
        sprintf(result, "%d", drops);
    }
    else
    {
        *ptr = '\0';
    }

    return result;
}