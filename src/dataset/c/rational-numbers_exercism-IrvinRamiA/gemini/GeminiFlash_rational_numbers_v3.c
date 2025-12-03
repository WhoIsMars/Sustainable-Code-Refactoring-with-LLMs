#include "rational_numbers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static rational_t result = {0, 1};

static int8_t maximum_common_divisor(int8_t a, int8_t b)
{
    a = abs(a);
    b = abs(b);

    while (b != 0) {
        int8_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

rational_t add(rational_t a, rational_t b)
{
    result.numerator = (int16_t)a.numerator * b.denominator + (int16_t)a.denominator * b.numerator;
    result.denominator = (int16_t)a.denominator * b.denominator;

    return reduce(result);
}

rational_t subtract(rational_t a, rational_t b)
{
    result.numerator = (int16_t)a.numerator * b.denominator - (int16_t)a.denominator * b.numerator;
    result.denominator = (int16_t)a.denominator * b.denominator;

    return reduce(result);
}

rational_t multiply(rational_t a, rational_t b)
{
    result.numerator = (int16_t)a.numerator * b.numerator;
    result.denominator = (int16_t)a.denominator * b.denominator;

    return reduce(result);
}

rational_t divide(rational_t a, rational_t b)
{
    if (b.numerator == 0) {
        result.numerator = 0;
        result.denominator = 0;
        return result;
    }

    result.numerator = (int16_t)a.numerator * b.denominator;
    result.denominator = (int16_t)a.denominator * b.numerator;

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
    if (n == 0) {
        result.numerator = 1;
        result.denominator = 1;
        return result;
    }

    result.numerator = 1;
    result.denominator = 1;

    if (n > 0) {
        for (int8_t i = 0; i < n; ++i) {
            result.numerator *= r.numerator;
            result.denominator *= r.denominator;
        }
    } else {
        for (int8_t i = 0; i < -n; ++i) {
            result.numerator *= r.denominator;
            result.denominator *= r.numerator;
        }
    }

    return reduce(result);
}

float exp_real(uint8_t x, rational_t r)
{
    float rational = (float)r.numerator / (float)r.denominator;

    return powf((float)x, rational);
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