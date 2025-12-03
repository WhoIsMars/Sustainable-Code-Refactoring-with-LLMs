#include "roman_numerals.h"
#include <stdlib.h>
#include <string.h>

#define BASE_ROMAN_NUMERALS_LEN         13
#define MAX_STRING_ROMAN_NUMERAL_LEN    16 // Increased size for safety

static const roman_numeral_t base_roman_numerals[BASE_ROMAN_NUMERALS_LEN] = {
    {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"},
    {50, "L"},   {40, "XL"},  {10, "X"},  {9, "IX"},   {5, "V"},  {4, "IV"},
    {1, "I"}
};

char *to_roman_numeral(unsigned int number) {
    char *roman_number = (char *)malloc(MAX_STRING_ROMAN_NUMERAL_LEN * sizeof(char));
    if (roman_number == NULL) {
        return NULL; // Handle allocation failure
    }

    char *ptr = roman_number; // Use a pointer to build the string
    size_t remaining_size = MAX_STRING_ROMAN_NUMERAL_LEN - 1; // Account for null terminator

    for (int i = 0; i < BASE_ROMAN_NUMERALS_LEN; ++i) {
        while (number >= base_roman_numerals[i].decimal_value) {
            size_t symbol_len = strlen(base_roman_numerals[i].symbol);

            if (symbol_len > remaining_size) {
                free(roman_number);
                return NULL; // Handle potential buffer overflow
            }

            strncpy(ptr, base_roman_numerals[i].symbol, symbol_len);
            ptr += symbol_len;
            remaining_size -= symbol_len;
            number -= base_roman_numerals[i].decimal_value;
        }
    }

    *ptr = '\0'; // Null-terminate the string
    return roman_number;
}