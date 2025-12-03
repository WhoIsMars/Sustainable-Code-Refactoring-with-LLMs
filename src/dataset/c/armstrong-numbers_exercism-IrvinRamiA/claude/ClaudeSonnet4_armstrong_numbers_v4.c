#include "armstrong_numbers.h"

enum
{
    ZERO = 0,
    ONE = 1,
    TEN = 10
};

static uint32_t power_table[10][10] = {
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 4, 8, 16, 32, 64, 128, 256, 512},
    {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683},
    {1, 4, 16, 64, 256, 1024, 4096, 16384, 65536, 262144},
    {1, 5, 25, 125, 625, 3125, 15625, 78125, 390625, 1953125},
    {1, 6, 36, 216, 1296, 7776, 46656, 279936, 1679616, 10077696},
    {1, 7, 49, 343, 2401, 16807, 117649, 823543, 5764801, 40353607},
    {1, 8, 64, 512, 4096, 32768, 262144, 2097152, 16777216, 134217728},
    {1, 9, 81, 729, 6561, 59049, 531441, 4782969, 43046721, 387420489}
};

static uint32_t power(uint8_t base, uint8_t exponent)
{
    if (exponent < 10 && base < 10) {
        return power_table[base][exponent];
    }
    
    uint32_t result = ONE;
    while (exponent--) {
        result *= base;
    }
    return result;
}

bool is_armstrong_number(uint32_t candidate)
{
    if (candidate == ZERO) {
        return true;
    }
    
    uint32_t temp = candidate;
    uint8_t digits = ZERO;
    
    while (temp) {
        digits++;
        temp /= TEN;
    }
    
    temp = candidate;
    uint32_t sum = ZERO;
    
    while (temp) {
        uint8_t digit = temp % TEN;
        sum += power(digit, digits);
        temp /= TEN;
    }
    
    return candidate == sum;
}