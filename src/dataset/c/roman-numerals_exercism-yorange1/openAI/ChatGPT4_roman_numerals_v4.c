#include "roman_numerals.h"

#include <assert.h>
#include <stdlib.h>

#define MAX_LEN (20)

char *to_roman_numeral(unsigned int number)
{
    static const char *roman_table[4][10] = {
        {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
        {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
        {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
        {"", "M", "MM", "MMM"}
    };

    char *roman = malloc(MAX_LEN);
    assert(roman != NULL);

    char *ptr = roman;
    unsigned int base = 1000;

    for (int i = 3; i >= 0; i--)
    {
        int digit = number / base;
        if (digit)
        {
            const char *symbol = roman_table[i][digit];
            while (*symbol)
            {
                *ptr++ = *symbol++;
            }
        }
        number %= base;
        base /= 10;
    }

    *ptr = '\0';
    return roman;
}