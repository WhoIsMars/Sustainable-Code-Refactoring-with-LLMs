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
    *ptr = '\0';
    
    const int mod3 = drops % 3;
    const int mod5 = drops % 5;
    const int mod7 = drops % 7;
    
    if (mod3 == 0) {
        *ptr++ = 'P'; *ptr++ = 'l'; *ptr++ = 'i'; *ptr++ = 'n'; *ptr++ = 'g';
    }
    if (mod5 == 0) {
        *ptr++ = 'P'; *ptr++ = 'l'; *ptr++ = 'a'; *ptr++ = 'n'; *ptr++ = 'g';
    }
    if (mod7 == 0) {
        *ptr++ = 'P'; *ptr++ = 'l'; *ptr++ = 'o'; *ptr++ = 'n'; *ptr++ = 'g';
    }
    
    if (ptr == result) {
        sprintf(result, "%d", drops);
    } else {
        *ptr = '\0';
    }

    return result;
}