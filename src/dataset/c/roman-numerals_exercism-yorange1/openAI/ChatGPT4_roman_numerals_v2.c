#include "roman_numerals.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN (20)

char *to_roman_numeral(unsigned int number)
{
    static const char *roman_table[4][10] = {
        {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},   // digits
        {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},   // tens
        {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},   // hundreds
        {"", "M", "MM", "MMM"}                                          // thousands
    };

    char *roman = (char *)malloc(MAX_LEN);
    assert(roman != NULL);
    roman[0] = '\0'; // Initialize the string

    for (int i = 3, base = 1000; i >= 0; i--, base /= 10)
    {
        int digit = number / base;
        strcat(roman, roman_table[i][digit]);
        number %= base;
    }

    return roman;
}