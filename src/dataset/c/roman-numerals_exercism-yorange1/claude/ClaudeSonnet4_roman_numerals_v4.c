#include "roman_numerals.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN (16)

static const char* const roman_digits[] = {
    "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"
};

static const char* const roman_tens[] = {
    "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"
};

static const char* const roman_hundreds[] = {
    "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"
};

static const char* const roman_thousands[] = {
    "", "M", "MM", "MMM"
};

char *to_roman_numeral(unsigned int number)
{
    char *roman = (char *)malloc(MAX_LEN);
    assert(roman != NULL);
    
    char *ptr = roman;
    
    unsigned int thousands = number / 1000;
    if (thousands) {
        const char *src = roman_thousands[thousands];
        while (*src) *ptr++ = *src++;
    }
    
    unsigned int hundreds = (number % 1000) / 100;
    if (hundreds) {
        const char *src = roman_hundreds[hundreds];
        while (*src) *ptr++ = *src++;
    }
    
    unsigned int tens = (number % 100) / 10;
    if (tens) {
        const char *src = roman_tens[tens];
        while (*src) *ptr++ = *src++;
    }
    
    unsigned int digits = number % 10;
    if (digits) {
        const char *src = roman_digits[digits];
        while (*src) *ptr++ = *src++;
    }
    
    *ptr = '\0';
    
    return roman;
}