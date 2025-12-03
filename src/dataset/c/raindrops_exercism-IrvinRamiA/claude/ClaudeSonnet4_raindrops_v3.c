/**
 * @file raindrops.c
 * @brief If input is a number return the number as character,
 * if multiple of 3 => return Pling
 * if multiple of 5 => return Plang
 * if multiple of 7 => return Plong
 */

#include "raindrops.h"
#include <string.h>
#include <stdio.h>

const char *convert(char result[], int drops)
{
    char *ptr = result;
    *ptr = '\0';
    
    const int mod3 = drops % 3;
    const int mod5 = drops % 5;
    const int mod7 = drops % 7;
    
    if (mod3 == 0) {
        memcpy(ptr, "Pling", 5);
        ptr += 5;
    }
    if (mod5 == 0) {
        memcpy(ptr, "Plang", 5);
        ptr += 5;
    }
    if (mod7 == 0) {
        memcpy(ptr, "Plong", 5);
        ptr += 5;
    }
    
    if (ptr == result) {
        sprintf(result, "%d", drops);
    } else {
        *ptr = '\0';
    }

    return result;
}