#include "armstrong_numbers.h"

static const uint32_t POWERS_OF_10[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
};

static uint32_t fast_power(uint32_t base, uint8_t exponent)
{
    if (exponent == 0) return 1;
    if (exponent == 1) return base;
    
    uint32_t result = 1;
    while (exponent > 0) {
        if (exponent & 1) {
            result *= base;
        }
        base *= base;
        exponent >>= 1;
    }
    return result;
}

static uint8_t count_digits(uint32_t n)
{
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    return 10;
}

bool is_armstrong_number(uint32_t candidate)
{
    if (candidate == 0) return true;
    
    const uint8_t digits = count_digits(candidate);
    uint32_t sum = 0;
    uint32_t temp = candidate;
    
    while (temp > 0) {
        const uint32_t digit = temp % 10;
        sum += fast_power(digit, digits);
        temp /= 10;
    }
    
    return candidate == sum;
}