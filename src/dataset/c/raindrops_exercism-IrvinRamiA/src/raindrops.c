/**
 * @file raindrops.c
 * @brief If input is a number return the number as character,
 * if multiple of 3 => return Pling
 * if multiple of 5 => return Pling
 * if multiple of 7 => return Pling
 */

#include "raindrops.h"
#include <string.h>
#include <stdio.h>

const char *convert(char result[], int drops)
{
    if (drops % 3 == 0)
    {
        strcat(result, "Pling");
    }
    if (drops % 5 == 0)
    {
        strcat(result, "Plang");
    }
    if (drops % 7 == 0)
    {
        strcat(result, "Plong");
    }
    if (result[0] == 0)
    {
        sprintf(result, "%d", drops);
    }

    return result;
}
