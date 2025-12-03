#include "roman_numerals.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#define MAX_LEN (20)

char *to_roman_numeral(unsigned int number) {
    const char *roman_values[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const int arabic_values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

    char *roman = (char *)calloc(1, MAX_LEN);
    assert(roman != NULL);

    size_t roman_index = 0;
    for (int i = 0; i < 13; ++i) {
        while (number >= arabic_values[i]) {
            size_t len = strlen(roman_values[i]);
            if (roman_index + len >= MAX_LEN) {
                free(roman);
                return NULL;
            }
            strcpy(roman + roman_index, roman_values[i]);
            roman_index += len;
            number -= arabic_values[i];
        }
    }

    return roman;
}