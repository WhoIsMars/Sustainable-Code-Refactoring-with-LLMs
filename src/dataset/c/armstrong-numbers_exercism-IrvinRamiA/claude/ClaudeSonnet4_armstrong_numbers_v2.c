#include "armstrong_numbers.h"

static uint32_t power(uint8_t base, uint8_t exponent)
{
    uint32_t result = 1;
    uint32_t base_power = base;
    
    while (exponent > 0) {
        if (exponent & 1) {
            result *= base_power;
        }
        base_power *= base_power;
        exponent >>= 1;
    }
    
    return result;
}

bool is_armstrong_number(uint32_t candidate)
{
    if (candidate == 0) {
        return true;
    }

    uint32_t original = candidate;
    uint8_t number_of_digits = 0;
    uint32_t temp = candidate;
    
    // Count digits without log10
    while (temp > 0) {
        number_of_digits++;
        temp /= 10;
    }

    uint32_t sum = 0;
    temp = candidate;

    while (temp > 0) {
        uint8_t digit = temp % 10;
        sum += power(digit, number_of_digits);
        temp /= 10;
    }

    return original == sum;
}