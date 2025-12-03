#include "armstrong_numbers.h"

#include <stdint.h>
#include <stdbool.h>

bool is_armstrong_number(int candidate)
{
    if (candidate < 0)
    {
        return false;
    }

    int digits[10];
    int digit_count = 0;
    int temp = candidate;

    while (temp > 0)
    {
        digits[digit_count++] = temp % 10;
        temp /= 10;
    }

    int sum = 0;
    for (int i = 0; i < digit_count; i++)
    {
        int digit_power = 1;
        for (int j = 0; j < digit_count; j++)
        {
            digit_power *= digits[i];
        }
        sum += digit_power;

        if (sum > candidate)
        {
            return false;
        }
    }

    return (sum == candidate);
}