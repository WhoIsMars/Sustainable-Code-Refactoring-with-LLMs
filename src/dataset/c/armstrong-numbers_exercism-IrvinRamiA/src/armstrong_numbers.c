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
    
    for(uint8_t i = ZERO; i < exponent ; i++)
    {
        result *= base;
    }

    return result;
}

bool is_armstrong_number(uint32_t candidate)
{
    if (candidate <= ZERO)
    {
        return ONE;
    }

    uint32_t copy_candidate = candidate;
    uint8_t number_of_digits = log10(candidate) + 1;
    uint32_t sum = ZERO;

    for (uint8_t i = ZERO; i < number_of_digits; i++)
    {
        sum += power(copy_candidate % TEN, number_of_digits);                   // (last_digit) ^ (number_of_digits)
        copy_candidate = (uint32_t) (copy_candidate / TEN);                     // Advance to next digit from left to right
    }

    return candidate == sum;
}

/* First Iteration

#include "armstrong_numbers.h"

#include <math.h>
#include <stdio.h>

enum
{
    ZERO = 0,
    ONE,
    TEN = 10
};

static uint8_t get_number_of_digits(uint32_t candidate)
{
    if (candidate < TEN)
    {
        return ONE;
    }
    else
    {
        return ONE + get_number_of_digits(candidate / TEN);
    }
}

bool is_armstrong_number(uint32_t candidate)
{
    if (candidate <= ZERO)
    {
        return ONE;
    }

    uint32_t copy_candidate = candidate;
    uint8_t number_of_digits = get_number_of_digits(candidate);
    uint32_t sum = ZERO;

    for (uint8_t i = ZERO; i < number_of_digits; i++)
    {
        sum += pow(copy_candidate % TEN, number_of_digits);
        copy_candidate = (copy_candidate - copy_candidate % TEN) / TEN;
    }

    if (candidate == sum)
    {
        return true;
    }

    return false;
}*/
