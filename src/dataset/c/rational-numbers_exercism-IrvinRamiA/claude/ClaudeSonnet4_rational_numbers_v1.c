#include "rational_numbers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static inline int8_t gcd(int8_t a, int8_t b)
{
    a = abs(a);
    b = abs(b);
    
    while (b != 0)
    {
        int8_t temp = b;
        b = a % b;
        a = temp;
    }
    
    return a;
}

static inline int8_t int_pow(int8_t base, int8_t exp)
{
    if (exp == 0) return 1;
    if (exp == 1) return base;
    
    int8_t result = 1;
    int8_t current_base = base;
    
    while (exp > 0)
    {
        if (exp & 1)
            result *= current_base;
        current_base *= current_base;
        exp >>= 1;
    }
    
    return result;
}

rational_t add(rational_t a, rational_t b)
{
    rational_t result;
    result.numerator = a.numerator * b.denominator + a.denominator * b.numerator;
    result.denominator = a.denominator * b.denominator;

    return reduce(result);
}

rational_t subtract(rational_t a, rational_t b)
{
    rational_t result;
    result.numerator = a.numerator * b.denominator - a.denominator * b.numerator;
    result.denominator = a.denominator * b.denominator;

    return reduce(result);
}

rational_t multiply(rational_t a, rational_t b)
{
    rational_t result;
    result.numerator = a.numerator * b.numerator;
    result.denominator = a.denominator * b.denominator;

    return reduce(result);
}

rational_t divide(rational_t a, rational_t b)
{
    rational_t result;
    result.numerator = a.numerator * b.denominator;
    result.denominator = a.denominator * b.numerator;

    return reduce(result);
}

rational_t absolute(rational_t a)
{
    a.numerator = abs(a.numerator);
    a.denominator = abs(a.denominator);

    return a;
}

rational_t exp_rational(rational_t r, int8_t n)
{
    rational_t result;
    
    if (n == 0)
    {
        result.numerator = 1;
        result.denominator = 1;
        return result;
    }
    
    if (n < 0)
    {
        result.numerator = int_pow(r.denominator, -n);
        result.denominator = int_pow(r.numerator, -n);
    }
    else
    {
        result.numerator = int_pow(r.numerator, n);
        result.denominator = int_pow(r.denominator, n);
    }

    return result;
}

float exp_real(uint8_t x, rational_t r)
{
    float rational = (float)r.numerator / (float)r.denominator;
    return powf(x, rational);
}

rational_t reduce(rational_t r)
{
    if (r.numerator == 0)
    {
        r.denominator = 1;
        return r;
    }

    if (r.denominator < 0)
    {
        r.numerator = -r.numerator;
        r.denominator = -r.denominator;
    }

    int8_t mcd = gcd(r.numerator, r.denominator);
    r.numerator /= mcd;
    r.denominator /= mcd;

    return r;
}