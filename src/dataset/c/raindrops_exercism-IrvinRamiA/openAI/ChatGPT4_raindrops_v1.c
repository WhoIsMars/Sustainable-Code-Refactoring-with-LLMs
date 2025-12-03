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
    int len = 0;

    if (drops % 3 == 0)
    {
        len += sprintf(result + len, "Pling");
    }
    if (drops % 5 == 0)
    {
        len += sprintf(result + len, "Plang");
    }
    if (drops % 7 == 0)
    {
        len += sprintf(result + len, "Plong");
    }
    if (len == 0)
    {
        sprintf(result, "%d", drops);
    }

    return result;
}