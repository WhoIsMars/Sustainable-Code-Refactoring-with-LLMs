#include "armstrong_numbers.h"

#include <inttypes.h>

enum
{
    ZERO = 0,
    ONE,
    TEN = 10
};

static uint32_t power(uint32_t base, uint8_t exponent) {
    uint32_t result = 1;
    for (uint8_t i = 0; i < exponent; ++i) {
        if (result > UINT32_MAX / base) return UINT32_MAX; // Check for potential overflow
        result *= base;
    }
    return result;
}

bool is_armstrong_number(uint32_t candidate) {
    if (candidate == 0) {
        return true;
    }

    uint32_t temp = candidate;
    uint8_t num_digits = 0;
    while (temp != 0) {
        temp /= 10;
        num_digits++;
    }

    temp = candidate;
    uint32_t sum = 0;
    while (temp != 0) {
        uint32_t digit = temp % 10;
        uint32_t pow_val = power(digit, num_digits);
        if (UINT32_MAX - sum < pow_val) return false; // Check for potential overflow
        sum += pow_val;
        temp /= 10;
    }

    return sum == candidate;
}