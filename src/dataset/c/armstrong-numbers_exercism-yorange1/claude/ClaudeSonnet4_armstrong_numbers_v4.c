#include "armstrong_numbers.h"

#include <stdio.h>
#include <stdint.h>

static const int pow_table[10][10] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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

bool is_armstrong_number(int candidate)
{
    if (candidate <= 0)
    {
        return candidate == 0;
    }

    int temp = candidate;
    int digit_count = 0;
    
    while (temp > 0)
    {
        digit_count++;
        temp /= 10;
    }

    if (digit_count > 9)
    {
        return false;
    }

    int sum = 0;
    temp = candidate;

    while (temp > 0)
    {
        int digit = temp % 10;
        sum += pow_table[digit][digit_count];
        temp /= 10;

        if (sum > candidate)
        {
            return false;
        }
    }

    return sum == candidate;
}