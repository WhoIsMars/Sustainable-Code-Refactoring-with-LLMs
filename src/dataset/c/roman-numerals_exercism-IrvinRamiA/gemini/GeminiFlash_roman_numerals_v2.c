#include "roman_numerals.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BASE_ROMAN_NUMERALS_LEN         13
#define MAX_STRING_ROMAN_NUMERAL_LEN    16 // Increased size for safety

static const roman_numeral_t base_roman_numerals[BASE_ROMAN_NUMERALS_LEN] = {
    {1, "I"}, {4, "IV"}, {5, "V"}, {9, "IX"}, {10, "X"}, {40, "XL"}, {50, "L"},
    {90, "XC"}, {100, "C"}, {400, "CD"}, {500, "D"}, {900, "CM"}, {1000, "M"}
};

char *to_roman_numeral(unsigned int number) {
    char *roman_number = (char *)malloc(MAX_STRING_ROMAN_NUMERAL_LEN * sizeof(char));
    if (roman_number == NULL) {
        return NULL; // Handle allocation failure
    }
    roman_number[0] = '\0';

    size_t current_length = 0;

    for (int i = BASE_ROMAN_NUMERALS_LEN - 1; i >= 0; i--) {
        while (number >= base_roman_numerals[i].decimal_value) {
            size_t symbol_length = strlen(base_roman_numerals[i].symbol);

            if (current_length + symbol_length >= MAX_STRING_ROMAN_NUMERAL_LEN) {
                free(roman_number);
                return NULL; // Handle potential buffer overflow
            }

            strcat(roman_number, base_roman_numerals[i].symbol);
            number -= base_roman_numerals[i].decimal_value;
            current_length += symbol_length;
        }
    }

    return roman_number;
}