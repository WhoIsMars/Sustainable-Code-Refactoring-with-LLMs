#include "roman_numerals.h"

#include <stdlib.h>
#include <string.h>

#define MAX_LEN (20)

char *to_roman_numeral(unsigned int number) {
    const struct {
        int value;
        char *symbol;
    } roman_map[] = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
        {90, "XC"},  {50, "L"},   {40, "XL"},  {10, "X"},  {9, "IX"},
        {5, "V"},    {4, "IV"},   {1, "I"}};

    char *roman = (char *)calloc(1, MAX_LEN);
    if (roman == NULL) {
        return NULL; // Handle allocation failure
    }

    int i = 0;
    while (number > 0 && i < sizeof(roman_map) / sizeof(roman_map[0])) {
        if (number >= roman_map[i].value) {
            strcat(roman, roman_map[i].symbol);
            number -= roman_map[i].value;
        } else {
            i++;
        }
    }

    return roman;
}