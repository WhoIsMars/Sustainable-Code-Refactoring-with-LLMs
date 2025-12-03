#include "roman_numerals.h"
#include <stdlib.h>
#include <string.h>

#define BASE_ROMAN_NUMERALS_LEN         13
#define MAX_STRING_ROMAN_NUMERAL_LEN    16

static const roman_numeral_t base_roman_numerals[BASE_ROMAN_NUMERALS_LEN] = {{1000, "M"},
                                                                             {900, "CM"},
                                                                             {500, "D"},
                                                                             {400, "CD"},
                                                                             {100, "C"},
                                                                             {90, "XC"},
                                                                             {50, "L"},
                                                                             {40, "XL"},
                                                                             {10, "X"},
                                                                             {9, "IX"},
                                                                             {5, "V"},
                                                                             {4, "IV"},
                                                                             {1, "I"}};

char *to_roman_numeral(unsigned int number)
{
    char *roman_number = (char *)calloc(MAX_STRING_ROMAN_NUMERAL_LEN, sizeof(char));
    char *ptr = roman_number;

    for (uint8_t i = 0; i < BASE_ROMAN_NUMERALS_LEN && number > 0; i++)
    {
        while (number >= base_roman_numerals[i].decimal_value)
        {
            strcpy(ptr, base_roman_numerals[i].symbol);
            ptr += strlen(base_roman_numerals[i].symbol);
            number -= base_roman_numerals[i].decimal_value;
        }
    }

    return roman_number;
}