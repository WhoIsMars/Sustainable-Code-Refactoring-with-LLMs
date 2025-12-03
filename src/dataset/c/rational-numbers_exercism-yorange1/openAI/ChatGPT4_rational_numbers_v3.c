#include "rational_numbers.h"

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define is_even(x) (((x) & 1) == 0)

static uint16_t gcd(uint16_t a, uint16_t b)
{
    while (b != 0)
    {
        uint16_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

rational_t add(rational_t r1, rational_t r2)
{
    rational_t ret;

    ret.numerator = r1.numerator * r2.denominator + r2.numerator * r1.denominator;
    ret.denominator = r1.denominator * r2.denominator;

    return reduce(ret);
}

rational_t subtract(rational_t r1, rational_t r2)
{
    rational_t ret;

    ret.numerator = r1.numerator * r2.denominator - r2.numerator * r1.denominator;
    ret.denominator = r1.denominator * r2.denominator;

    return reduce(ret);
}

rational_t multiply(rational_t r1, rational_t r2)
{
    if (r1.numerator == 0 || r2.numerator == 0)
    {
        return (rational_t){0, 1};
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
    return (rational_t){abs(r.numerator), abs(r.denominator)};
}

rational_t reduce(rational_t r)
{
    if (r.numerator == 0)
    {
        return (rational_t){0, 1};
    }

    uint16_t gcd_n = gcd(abs(r.numerator), abs(r.denominator));

    r.numerator /= gcd_n;
    r.denominator /= gcd_n;

    if (r.denominator < 0)
    {
        r.denominator *= -1;
        r.numerator *= -1;
    }

    return r;
}

rational_t exp_rational(rational_t r, uint16_t n)
{
    rational_t ret;

    ret.numerator = (int)pow(r.numerator, n);
    ret.denominator = (int)pow(r.denominator, n);

    return reduce(ret);
}

float exp_real(uint16_t x, rational_t r)
{
    return pow(x, (float)r.numerator / r.denominator);
}