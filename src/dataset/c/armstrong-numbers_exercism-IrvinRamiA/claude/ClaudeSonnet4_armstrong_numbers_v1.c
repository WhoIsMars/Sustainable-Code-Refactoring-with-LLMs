#include "armstrong_numbers.h"

enum
{
    ZERO = 0,
    ONE = 1,
    TEN = 10
};

static uint32_t power(uint8_t base, uint8_t exponent)
{
    if (exponent == ZERO) return ONE;
    if (exponent == ONE) return base;
    
    uint32_t result = ONE;
    uint32_t b = base;
    
    while (exponent > ZERO)
    {
        if (exponent & ONE)
        {
            result *= b;
        }
        b *= b;
        exponent >>= ONE;
    }
    
    return result;
}

bool is_armstrong_number(uint32_t candidate)
{
    if (candidate == ZERO) return true;
    if (candidate < ZERO) return false;

    uint32_t temp = candidate;
    uint8_t number_of_digits = ZERO;
    
    // Count digits without floating point operations
    while (temp > ZERO)
    {
        number_of_digits++;
        temp /= TEN;
    }

    temp = candidate;
    uint32_t sum = ZERO;

    while (temp > ZERO)
    {
        uint8_t digit = temp % TEN;
        sum += power(digit, number_of_digits);
        temp /= TEN;
    }

    return candidate == sum;
}