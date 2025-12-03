#include "rational_numbers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static rational_t result = {0, 0};

static int8_t maximum_common_divisor(int8_t a, int8_t b)
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

rational_t add(rational_t a, rational_t b)
{
    rational_t res;
    res.numerator = a.numerator * b.denominator + a.denominator * b.numerator;
    res.denominator = a.denominator * b.denominator;
    return reduce(res);
}

rational_t subtract(rational_t a, rational_t b)
{
    rational_t res;
    res.numerator = a.numerator * b.denominator - a.denominator * b.numerator;
    res.denominator = a.denominator * b.denominator;
    return reduce(res);
}

rational_t multiply(rational_t a, rational_t b)
{
    rational_t res;
    res.numerator = a.numerator * b.numerator;
    res.denominator = a.denominator * b.denominator;
    return reduce(res);
}

rational_t divide(rational_t a, rational_t b)
{
    rational_t res;
    res.numerator = a.numerator * b.denominator;
    res.denominator = a.denominator * b.numerator;
    return reduce(res);
}

rational_t absolute(rational_t a)
{
    a.numerator = abs(a.numerator);
    a.denominator = abs(a.denominator);
    return a;
}

rational_t exp_rational(rational_t r, int8_t n)
{
    rational_t res;
    res.numerator = pow(r.numerator, n);
    res.denominator = pow(r.denominator, n);
    return res;
}

float exp_real(uint8_t x, rational_t r)
{
    return powf(x, (float)r.numerator / r.denominator);
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

    int8_t mcd = maximum_common_divisor(r.numerator, r.denominator);
    r.numerator /= mcd;
    r.denominator /= mcd;

    return r;
}