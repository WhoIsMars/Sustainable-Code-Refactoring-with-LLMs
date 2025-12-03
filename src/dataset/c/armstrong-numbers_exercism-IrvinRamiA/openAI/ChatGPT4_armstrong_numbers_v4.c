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

static uint8_t get_number_of_digits(uint32_t candidate)
{
    uint8_t digits = ONE;
    while (candidate >= TEN)
    {
        candidate /= TEN;
        digits++;
    }
    return digits;
}

bool is_armstrong_number(uint32_t candidate)
{
    if (candidate == ZERO)
    {
        return true;
    }

    uint32_t copy_candidate = candidate;
    uint8_t number_of_digits = get_number_of_digits(candidate);
    uint32_t sum = ZERO;

    while (copy_candidate > ZERO)
    {
        uint8_t digit = copy_candidate % TEN;
        sum += power(digit, number_of_digits);
        copy_candidate /= TEN;
    }

    return candidate == sum;
}