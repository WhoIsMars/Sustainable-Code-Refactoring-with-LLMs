#include "rational_numbers.h"

#include <math.h>

#include <stdlib.h>
#include <stdbool.h>

static uint16_t gcd(uint16_t a, uint16_t b)
{
    while (b != 0) {
        uint16_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

rational_t add(rational_t r1, rational_t r2)
{
    rational_t ret;
    ret.numerator = (int32_t)r1.numerator * r2.denominator + (int32_t)r2.numerator * r1.denominator;
    ret.denominator = (int32_t)r1.denominator * r2.denominator;
    return reduce(ret);
}

rational_t subtract(rational_t r1, rational_t r2)
{
    rational_t ret;
    ret.numerator = (int32_t)r1.numerator * r2.denominator - (int32_t)r2.numerator * r1.denominator;
    ret.denominator = (int32_t)r1.denominator * r2.denominator;
    return reduce(ret);
}

rational_t multiply(rational_t r1, rational_t r2)
{
    rational_t ret;
    if (r1.numerator == 0 || r2.numerator == 0)
    {
        ret.numerator = 0;
        ret.denominator = 1;
        return ret;
    }

    ret.numerator = (int32_t)r1.numerator * r2.numerator;
    ret.denominator = (int32_t)r1.denominator * r2.denominator;

    return reduce(ret);
}

rational_t divide(rational_t r1, rational_t r2)
{
    rational_t ret;
    ret.numerator = (int32_t)r1.numerator * r2.denominator;
    ret.denominator = (int32_t)r1.denominator * r2.numerator;
    
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
    if (r.numerator == 0) {
        rational_t ret = {0, 1};
        return ret;
    }

    int16_t sign_num = (r.numerator < 0) ? -1 : 1;
    int16_t sign_den = (r.denominator < 0) ? -1 : 1;

    uint16_t num = abs(r.numerator);
    uint16_t den = abs(r.denominator);

    uint16_t common = gcd(num, den);

    rational_t ret;
    ret.numerator = sign_num * (r.numerator / common);
    ret.denominator = sign_den * (r.denominator / common);

    if (ret.denominator < 0) {
        ret.denominator *= -1;
        ret.numerator *= -1;
    }

    return ret;
}

rational_t exp_rational(rational_t r, uint16_t n)
{
    rational_t ret;
    ret.numerator = 1;
    ret.denominator = 1;

    for (uint16_t i = 0; i < n; ++i) {
        ret.numerator *= r.numerator;
        ret.denominator *= r.denominator;
    }

    return reduce(ret);
}

float exp_real(uint16_t x, rational_t r)
{
    return pow(pow(x, (double)r.numerator), 1.0 / r.denominator);
}