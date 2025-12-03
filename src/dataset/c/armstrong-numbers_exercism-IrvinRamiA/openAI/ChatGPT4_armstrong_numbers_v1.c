#include "armstrong_numbers.h"

enum
{
    ZERO = 0,
    ONE,
    TEN = 10
};

static uint32_t power(uint8_t base, uint8_t exponent)
{
    uint32_t result = ONE;
    while (exponent--)
    {
        result *= base;
    }
    return result;
}

bool is_armstrong_number(uint32_t candidate)
{
    if (candidate == ZERO)
    {
        return true;
    }

    uint32_t copy_candidate = candidate;
    uint32_t sum = ZERO;
    uint8_t number_of_digits = 0;
    uint32_t temp = candidate;

    // Calculate number of digits
    while (temp)
    {
        temp /= TEN;
        number_of_digits++;
    }

    // Calculate Armstrong sum
    while (copy_candidate)
    {
        uint8_t digit = copy_candidate % TEN;
        sum += power(digit, number_of_digits);
        copy_candidate /= TEN;
    }

    return candidate == sum;
}