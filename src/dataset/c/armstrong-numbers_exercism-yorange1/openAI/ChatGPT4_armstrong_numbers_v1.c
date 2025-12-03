#include "armstrong_numbers.h"

#include <stdint.h>
#include <stdbool.h>

bool is_armstrong_number(int candidate)
{
    if (candidate < 0)
    {
        return false;
    }
    if (candidate == 0)
    {
        return true;
    }

    int exponent = 0, temp = candidate, sum = 0;
    int digits[10]; // To store digits of the number
    int digit_count = 0;

    // Extract digits and count them
    while (temp > 0)
    {
        digits[digit_count++] = temp % 10;
        temp /= 10;
    }
    exponent = digit_count;

    // Calculate the Armstrong sum
    for (int i = 0; i < digit_count; i++)
    {
        int digit_power = 1;
        for (int j = 0; j < exponent; j++)
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