#include "rational_numbers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static rational_t result = {0, 0};

static int8_t maximum_common_divisor(rational_t r)
{
    int8_t mcd = 0;
    int8_t mod = 0;
    int8_t current_num = 0;
    int8_t current_den = 0;

    /* First condition of Euclides algorithm */
    r.numerator = abs(r.numerator);
    r.denominator = abs(r.denominator);
    if (r.numerator > r.denominator)
    {
        current_num = r.numerator;
        current_den = r.denominator;
    }
    else
    {
        current_num = r.denominator;
        current_den = r.numerator;
    }

    /* Euclides algorith to calculate mcd */
    do
    {
        mod = current_num % current_den;
        if (mod == 0)
        {
            mcd = current_den;
        }
        current_num = current_den;
        current_den = mod;
    } while (mod != 0);

    return mcd;
}

rational_t add(rational_t a, rational_t b)
{
    result.numerator = a.numerator * b.denominator + a.denominator * b.numerator;
    result.denominator = a.denominator * b.denominator;

    return reduce(result);
}

rational_t subtract(rational_t a, rational_t b)
{
    result.numerator = a.numerator * b.denominator - a.denominator * b.numerator;
    result.denominator = a.denominator * b.denominator;

    return reduce(result);
}

rational_t multiply(rational_t a, rational_t b)
{
    result.numerator = a.numerator * b.numerator;
    result.denominator = a.denominator * b.denominator;

    return reduce(result);
}

rational_t divide(rational_t a, rational_t b)
{
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
    result.numerator = pow(r.numerator, n);
    result.denominator = pow(r.denominator, n);

    return result;
}

float exp_real(uint8_t x, rational_t r)
{
    float rational = (float)r.numerator / (float)r.denominator;

    return pow(x, rational);
}

rational_t reduce(rational_t r)
{
    /* Evaluation to find a rational number with numerator equal to 0 */
    /* The denominator is set to 1 */
    if (r.numerator == 0)
    {
        r.denominator = 1;
        return r;
    }

    /* Evaluation to find a rational number with negative denominator */
    /* If numerator is negative and denominator is negative both are multiplied by -1 */
    /* If numerator is positive and denominator is negative both are multiplied by -1 */
    if (r.denominator < 0)
    {
        r.numerator = -1 * r.numerator;
        r.denominator = -1 * r.denominator;
    }

    /* Final reduction step -> Calculate mcd and reduce rational number */
    int8_t mcd = maximum_common_divisor(r);
    r.numerator /= mcd;
    r.denominator /= mcd;

    return r;
}
