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
    
    uint16_t common_gcd = gcd(r1.denominator, r2.denominator);
    int d1 = r1.denominator / common_gcd;
    int d2 = r2.denominator / common_gcd;
    
    rational_t ret;
    ret.numerator = r1.numerator * d2 + r2.numerator * d1;
    ret.denominator = r1.denominator * d2;
    
    return reduce(ret);
}

rational_t subtract(rational_t r1, rational_t r2)
{
    if (r2.numerator == 0) return r1;
    
    uint16_t common_gcd = gcd(r1.denominator, r2.denominator);
    int d1 = r1.denominator / common_gcd;
    int d2 = r2.denominator / common_gcd;
    
    rational_t ret;
    ret.numerator = r1.numerator * d2 - r2.numerator * d1;
    ret.denominator = r1.denominator * d2;
    
    return reduce(ret);
}

rational_t multiply(rational_t r1, rational_t r2)
{
    if (r1.numerator == 0 || r2.numerator == 0)
    {
        rational_t ret = {0, 1};
        return ret;
    }

    uint16_t gcd1 = gcd(abs(r1.numerator), abs(r2.denominator));
    uint16_t gcd2 = gcd(abs(r2.numerator), abs(r1.denominator));
    
    rational_t ret;
    ret.numerator = (r1.numerator / gcd1) * (r2.numerator / gcd2);
    ret.denominator = (r1.denominator / gcd2) * (r2.denominator / gcd1);
    
    if (ret.denominator < 0)
    {
        ret.denominator = -ret.denominator;
        ret.numerator = -ret.numerator;
    }
    
    return ret;
}

rational_t divide(rational_t r1, rational_t r2)
{
    rational_t r2_inv = {r2.denominator, r2.numerator};
    return multiply(r1, r2_inv);
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
    
    uint16_t common_gcd = gcd(abs(r.numerator), abs(r.denominator));
    
    rational_t ret;
    ret.numerator = r.numerator / common_gcd;
    ret.denominator = r.denominator / common_gcd;
    
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
    
    rational_t ret = {1, 1};
    rational_t base = r;
    
    while (n > 0)
    {
        if (n & 1)
        {
            ret = multiply(ret, base);
        }
        base = multiply(base, base);
        n >>= 1;
    }
    
    return ret;
}

float exp_real(uint16_t x, rational_t r)
{
    if (r.numerator == 0) return 1.0f;
    if (x == 0) return 0.0f;
    if (x == 1) return 1.0f;
    
    return powf(powf((float)x, (float)r.numerator), 1.0f / (float)r.denominator);
}