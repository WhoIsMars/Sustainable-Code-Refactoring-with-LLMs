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

    int temp = candidate;
    int exponent = 0;
    int digits[10];
    int digit_count = 0;

    // Extract digits and calculate the number of digits (exponent)
    while (temp > 0)
    {
        digits[digit_count++] = temp % 10;
        temp /= 10;
        exponent++;
    }

    int sum = 0;
    for (int i = 0; i < digit_count; i++)
    {
        int power = 1;
        for (int j = 0; j < exponent; j++)
        {
            power *= digits[i];
        }
        sum += power;

        if (sum > candidate)
        {
            return false;
        }
    }

    return (sum == candidate);
}