#include "roman_numerals.h"

#include <stdlib.h>
#include <string.h>

#define MAX_LEN (20)

char *to_roman_numeral(unsigned int number) {
    const char *roman_table[][10] = {
        {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},   // digits
        {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},   // tens
        {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},   // hundreds
        {"", "M", "MM", "MMM"}                                          // thousands
    };

    char *roman = (char *)malloc(MAX_LEN);
    if (roman == NULL) return NULL;  // Handle allocation failure

    roman[0] = '\0'; // Initialize as empty string

    int base_index = 3;
    unsigned int base = 1000;
    while (base > 0) {
        int digit = number / base;
        if (digit != 0) {
            strcat(roman, roman_table[base_index][digit]);
        }
        number %= base;
        base /= 10;
        base_index--;
    }

    return roman;
}