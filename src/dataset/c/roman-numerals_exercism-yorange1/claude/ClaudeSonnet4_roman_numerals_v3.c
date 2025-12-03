#include "roman_numerals.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN (16)

char *to_roman_numeral(unsigned int number)
{
    static const char* const roman_numerals[] = {
        "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX",
        "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC",
        "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM",
        "", "M", "MM", "MMM"
    };
    
    static const int offsets[] = {30, 20, 10, 0};
    static const unsigned int divisors[] = {1000, 100, 10, 1};

    char *roman = (char *)malloc(MAX_LEN);
    assert(roman != NULL);
    
    char *ptr = roman;
    *ptr = '\0';

    for (int i = 0; i < 4; i++)
    {
        unsigned int digit = number / divisors[i];
        if (digit != 0)
        {
            const char *numeral = roman_numerals[offsets[i] + digit];
            while (*numeral)
            {
                *ptr++ = *numeral++;
            }
            number %= divisors[i];
        }
    }
    
    *ptr = '\0';
    return roman;
}