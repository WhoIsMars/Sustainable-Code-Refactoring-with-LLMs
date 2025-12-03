#include "roman_numerals.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN (16)

char *to_roman_numeral(unsigned int number)
{
    static const char* const roman_table[4][10] = {
        {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
        {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
        {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
        {"", "M", "MM", "MMM"}
    };

    char *roman = (char *)malloc(MAX_LEN);
    assert(roman != NULL);
    
    char *ptr = roman;
    *ptr = '\0';

    if (number >= 1000) {
        int thousands = number / 1000;
        const char *src = roman_table[3][thousands];
        while (*src) *ptr++ = *src++;
        number %= 1000;
    }

    if (number >= 100) {
        int hundreds = number / 100;
        const char *src = roman_table[2][hundreds];
        while (*src) *ptr++ = *src++;
        number %= 100;
    }

    if (number >= 10) {
        int tens = number / 10;
        const char *src = roman_table[1][tens];
        while (*src) *ptr++ = *src++;
        number %= 10;
    }

    if (number > 0) {
        const char *src = roman_table[0][number];
        while (*src) *ptr++ = *src++;
    }

    *ptr = '\0';
    return roman;
}