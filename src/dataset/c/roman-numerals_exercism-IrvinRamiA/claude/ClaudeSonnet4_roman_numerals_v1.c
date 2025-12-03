#include "roman_numerals.h"
#include <stdlib.h>
#include <string.h>

#define BASE_ROMAN_NUMERALS_LEN         13
#define MAX_STRING_ROMAN_NUMERAL_LEN    16

typedef struct {
    unsigned int decimal_value;
    const char *symbol;
    uint8_t symbol_len;
} roman_numeral_optimized_t;

static const roman_numeral_optimized_t base_roman_numerals[BASE_ROMAN_NUMERALS_LEN] = {
    {1000, "M", 1},
    {900, "CM", 2},
    {500, "D", 1},
    {400, "CD", 2},
    {100, "C", 1},
    {90, "XC", 2},
    {50, "L", 1},
    {40, "XL", 2},
    {10, "X", 1},
    {9, "IX", 2},
    {5, "V", 1},
    {4, "IV", 2},
    {1, "I", 1}
};

char *to_roman_numeral(unsigned int number)
{
    char *roman_number = (char *)malloc(MAX_STRING_ROMAN_NUMERAL_LEN * sizeof(char));
    char *ptr = roman_number;
    
    for (uint8_t i = 0; i < BASE_ROMAN_NUMERALS_LEN; i++)
    {
        while (number >= base_roman_numerals[i].decimal_value)
        {
            memcpy(ptr, base_roman_numerals[i].symbol, base_roman_numerals[i].symbol_len);
            ptr += base_roman_numerals[i].symbol_len;
            number -= base_roman_numerals[i].decimal_value;
        }
    }
    
    *ptr = '\0';
    return roman_number;
}