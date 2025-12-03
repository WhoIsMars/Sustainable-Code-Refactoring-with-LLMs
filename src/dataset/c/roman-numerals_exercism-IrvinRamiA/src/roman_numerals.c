#include "roman_numerals.h"
#include <stdlib.h>
#include <string.h>

#define BASE_ROMAN_NUMERALS_LEN         13
#define MAX_STRING_ROMAN_NUMERAL_LEN    10

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
    char *roman_number = (char *)malloc(MAX_STRING_ROMAN_NUMERAL_LEN * sizeof(char));
    uint8_t len = 0;
    uint8_t total_len = 0;

    roman_number[0] = '\0';

    for (uint8_t i = BASE_ROMAN_NUMERALS_LEN; i > 0; i--)
    {
        while (number >= base_roman_numerals[i - 1].decimal_value)
        {
            len = strlen(base_roman_numerals[i - 1].symbol);
            total_len += len;
            strncat(roman_number, base_roman_numerals[i - 1].symbol, len);
            number -= base_roman_numerals[i - 1].decimal_value;
        }
    }

    roman_number[total_len] = '\0';

    return roman_number;
}
