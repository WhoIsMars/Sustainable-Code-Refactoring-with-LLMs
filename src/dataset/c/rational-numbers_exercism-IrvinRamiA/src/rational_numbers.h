#ifndef RATIONAL_NUMBERS
#define RATIONAL_NUMBERS

#include <stdint.h>

typedef struct
{
    int8_t numerator;
    int8_t denominator;
} rational_t;

rational_t add(rational_t a, rational_t b);
rational_t subtract(rational_t a, rational_t b);
rational_t multiply(rational_t a, rational_t b);
rational_t divide(rational_t a, rational_t b);
rational_t absolute(rational_t a);
rational_t exp_rational(rational_t r, int8_t n);
float exp_real(uint8_t x, rational_t r);
rational_t reduce(rational_t r);

#endif
