#include "rational_numbers.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

static uint16_t gcd(uint16_t a, uint16_t b) {
    if (a == 0) return b;
    if (b == 0) return a;

    uint16_t shift = 0;
    while (((a | b) & 1) == 0) {
        a >>= 1;
        b >>= 1;
        shift++;
    }

    while ((a & 1) == 0) a >>= 1;

    do {
        while ((b & 1) == 0) b >>= 1;

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
    ret.denominator = (uint32_t)r1.denominator * r2.denominator;
    return reduce(ret);
}

rational_t subtract(rational_t r1, rational_t r2) {
    rational_t ret;
    ret.numerator = (int32_t)r1.numerator * r2.denominator - (int32_t)r2.numerator * r1.denominator;
    ret.denominator = (uint32_t)r1.denominator * r2.denominator;
    return reduce(ret);
}

rational_t multiply(rational_t r1, rational_t r2) {
    rational_t ret;
    if (r1.numerator == 0 || r2.numerator == 0) {
        ret.numerator = 0;
        ret.denominator = 1;
        return ret;
    }
    ret.numerator = (int32_t)r1.numerator * r2.numerator;
    ret.denominator = (uint32_t)r1.denominator * r2.denominator;
    return reduce(ret);
}

rational_t divide(rational_t r1, rational_t r2) {
    rational_t ret;
    ret.numerator = (int32_t)r1.numerator * r2.denominator;
    ret.denominator = (uint32_t)r1.denominator * r2.numerator;
    return reduce(ret);
}

rational_t absolute(rational_t r) {
    rational_t ret;
    ret.numerator = abs(r.numerator);
    ret.denominator = r.denominator;
    return ret;
}

rational_t reduce(rational_t r) {
    if (r.numerator == 0) {
        rational_t ret = {0, 1};
        return ret;
    }

    int32_t num = r.numerator;
    uint32_t den = r.denominator;

    if (num < 0) {
        num = -num;
    }

    uint16_t common = gcd((uint16_t)num, (uint16_t)den);

    rational_t ret;
    ret.numerator = r.numerator / common;
    ret.denominator = r.denominator / common;

    if (ret.denominator < 0) {
        ret.denominator = -ret.denominator;
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
    uint32_t den = 1;

    for (uint16_t i = 0; i < n; ++i) {
        num *= r.numerator;
        den *= r.denominator;
    }

    ret.numerator = num;
    ret.denominator = den;
    return reduce(ret);
}

float exp_real(uint16_t x, rational_t r) {
    float base = (float)x;
    float exponent = (float)r.numerator / r.denominator;
    float result = 1.0;

    if (exponent == 0.0) return 1.0;

    if (exponent > 0) {
        result = powf(base, exponent);
    }

    return result;
}