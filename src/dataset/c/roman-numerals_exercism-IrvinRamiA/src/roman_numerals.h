#ifndef ROMAN_NUMERALS_H
#define ROMAN_NUMERALS_H

#include <stdint.h>

typedef struct
{
    uint16_t decimal_value;
    char *symbol;
} roman_numeral_t;

char *to_roman_numeral(unsigned int number);

#endif
