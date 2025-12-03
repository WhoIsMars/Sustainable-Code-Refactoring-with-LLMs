#include "armstrong_numbers.h"

#include <math.h>

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
    uint8_t digits[10]; // Store digits to avoid recalculating

    // Extract digits and count them
    while (copy_candidate > ZERO)
    {
        digits[number_of_digits++] = copy_candidate % TEN;
        copy_candidate /= TEN;
    }

    // Calculate the sum of powers
    for (uint8_t i = 0; i < number_of_digits; i++)
    {
        sum += power(digits[i], number_of_digits);
    }

    return candidate == sum;
}