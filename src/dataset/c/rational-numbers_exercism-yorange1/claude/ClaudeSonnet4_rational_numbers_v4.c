#include "rational_numbers.h"

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define is_even(x) ((x & 1) == 0)

static uint16_t gcd(int a, int b)
{
    if (b == 0) return abs(a);
    return gcd(b, a % b);
}

rational_t add(rational_t r1, rational_t r2)
{
    if (r1.numerator == 0) return r2;
    if (r2.numerator == 0) return r1;
    
    rational_t ret;
    ret.numerator = r1.numerator * r2.denominator + r2.numerator * r1.denominator;
    ret.denominator = r1.denominator * r2.denominator;

    return reduce(ret);
}

rational_t subtract(rational_t r1, rational_t r2)
{
    if (r2.numerator == 0) return r1;
    
    rational_t ret;
    ret.numerator = r1.numerator * r2.denominator - r2.numerator * r1.denominator;
    ret.denominator = r1.denominator * r2.denominator;

    return reduce(ret);
}

rational_t multiply(rational_t r1, rational_t r2)
{
    if (r1.numerator == 0 || r2.numerator == 0)
    {
        rational_t ret = {0, 1};
        return ret;
    }

    rational_t ret;
    ret.numerator = r1.numerator * r2.numerator;
    ret.denominator = r1.denominator * r2.denominator;

    return reduce(ret);
}

rational_t divide(rational_t r1, rational_t r2)
{
    rational_t ret;
    ret.numerator = r1.numerator * r2.denominator;
    ret.denominator = r1.denominator * r2.numerator;
    
    return reduce(ret);
}

rational_t absolute(rational_t r)
{
    rational_t ret;
    ret.numerator = abs(r.numerator);
    ret.denominator = abs(r.denominator);
    return ret;
}

rational_t reduce(rational_t r)
{
    if (r.numerator == 0)
    {
        rational_t ret = {0, 1};
        return ret;
    }
    
    uint16_t gcd_n = gcd(abs(r.numerator), abs(r.denominator));

    rational_t ret;
    ret.numerator = r.numerator / gcd_n;
    ret.denominator = r.denominator / gcd_n;

    if (ret.denominator < 0)
    {
        ret.denominator = -ret.denominator;
        ret.numerator = -ret.numerator;
    }

    return ret;
}

rational_t exp_rational(rational_t r, uint16_t n)
{
    if (n == 0)
    {
        rational_t ret = {1, 1};
        return ret;
    }
    
    if (r.numerator == 0)
    {
        rational_t ret = {0, 1};
        return ret;
    }

    rational_t ret;
    int num = r.numerator;
    int den = r.denominator;
    
    for (uint16_t i = 1; i < n; i++)
    {
        num *= r.numerator;
        den *= r.denominator;
    }
    
    ret.numerator = num;
    ret.denominator = den;

    return reduce(ret);
}

float exp_real(uint16_t x, rational_t r)
{
    return powf(powf((float)x, (float)r.numerator), 1.0f / (float)r.denominator);
}