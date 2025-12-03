#include "rational_numbers.h"

#include <stdlib.h>
#include <stdbool.h>

static uint16_t gcd(uint16_t a, uint16_t b) {
    if (a == 0) return b;
    if (b == 0) return a;

    uint16_t shift = 0;
    while (((a | b) & 1) == 0) {
        shift++;
        a >>= 1;
        b >>= 1;
    }

    while ((a & 1) == 0)
        a >>= 1;

    do {
        while ((b & 1) == 0)
            b >>= 1;

        if (a > b) {
            uint16_t temp = a;
            a = b;
            b = temp;
        }
        b = b - a;
    } while (b != 0);

    return a << shift;
}


rational_t add(rational_t r1, rational_t r2) {
    rational_t ret;
    ret.numerator = (int32_t)r1.numerator * r2.denominator + (int32_t)r2.numerator * r1.denominator;
    ret.denominator = (int32_t)r1.denominator * r2.denominator;
    return reduce(ret);
}

rational_t subtract(rational_t r1, rational_t r2) {
    rational_t ret;
    ret.numerator = (int32_t)r1.numerator * r2.denominator - (int32_t)r2.numerator * r1.denominator;
    ret.denominator = (int32_t)r1.denominator * r2.denominator;
    return reduce(ret);
}

rational_t multiply(rational_t r1, rational_t r2) {
    rational_t ret;
    ret.numerator = (int32_t)r1.numerator * r2.numerator;
    ret.denominator = (int32_t)r1.denominator * r2.denominator;
    return reduce(ret);
}

rational_t divide(rational_t r1, rational_t r2) {
    rational_t ret;
    ret.numerator = (int32_t)r1.numerator * r2.denominator;
    ret.denominator = (int32_t)r1.denominator * r2.numerator;
    return reduce(ret);
}

rational_t absolute(rational_t r) {
    rational_t ret;
    ret.numerator = abs(r.numerator);
    ret.denominator = abs(r.denominator);
    return ret;
}

rational_t reduce(rational_t r) {
    if (r.numerator == 0) {
        rational_t ret = {0, 1};
        return ret;
    }

    int16_t num = r.numerator;
    uint16_t den = r.denominator;

    bool num_neg = num < 0;
    if (num_neg) num = -num;

    uint16_t gcd_val = gcd((uint16_t)num, den);

    rational_t ret;
    ret.numerator = (int16_t)(r.numerator / gcd_val);
    ret.denominator = (uint16_t)(r.denominator / gcd_val);

    if (ret.denominator < 0) {
        ret.denominator = (uint16_t)(-ret.denominator);
        ret.numerator = -ret.numerator;
    }

    return ret;
}

rational_t exp_rational(rational_t r, uint16_t n) {
    rational_t ret;
    if (n == 0) {
        ret.numerator = 1;
        ret.denominator = 1;
        return ret;
    }

    if (n == 1) return r;

    int32_t num = 1;
    int32_t den = 1;

    for (uint16_t i = 0; i < n; ++i) {
        num *= r.numerator;
        den *= r.denominator;
    }

    ret.numerator = (int16_t)num;
    ret.denominator = (uint16_t)den;

    return reduce(ret);
}

float exp_real(uint16_t x, rational_t r) {
    float base = (float)x;
    float exponent = (float)r.numerator / r.denominator;
    return powf(base, exponent);
}