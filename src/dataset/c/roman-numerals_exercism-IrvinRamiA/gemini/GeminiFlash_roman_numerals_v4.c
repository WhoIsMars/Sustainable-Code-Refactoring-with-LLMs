#include "roman_numerals.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BASE_ROMAN_NUMERALS_LEN         13
#define MAX_STRING_ROMAN_NUMERAL_LEN    16 // Increased size for safety

static const roman_numeral_t base_roman_numerals[BASE_ROMAN_NUMERALS_LEN] = {{1, "I"},
                                                                             {4, "IV"},
                                                                             {5, "V"},
                                                                             {9, "IX"},
                                                                             {10, "X"},
                                                                             {40, "XL"},
                                                                             {50, "L"},
                                                                             {90, "XC"},
                                                                             {100, "C"},
                                                                             {400, "CD"},
                                                                             {500, "D"},
                                                                             {900, "CM"},
                                                                             {1000, "M"}};

char *to_roman_numeral(unsigned int number)
{
    char *roman_number = (char *)malloc(MAX_STRING_ROMAN_NUMERAL_LEN);
    if (!roman_number) return NULL; // Handle allocation failure

    char *ptr = roman_number;

    for (int i = BASE_ROMAN_NUMERALS_LEN - 1; i >= 0; i--)
    {
        while (number >= base_roman_numerals[i].decimal_value)
        {
            size_t len = strlen(base_roman_numerals[i].symbol);
            memcpy(ptr, base_roman_numerals[i].symbol, len);
            ptr += len;
            number -= base_roman_numerals[i].decimal_value;
        }
    }

    *ptr = '\0';
    return roman_number;
}