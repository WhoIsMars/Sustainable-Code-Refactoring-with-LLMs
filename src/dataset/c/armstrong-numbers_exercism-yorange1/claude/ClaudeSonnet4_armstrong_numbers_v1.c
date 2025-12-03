#include "armstrong_numbers.h"

#include <stdio.h>
#include <stdint.h>

bool is_armstrong_number(int candidate)
{
    if (candidate == 0)
    {
        return true;
    }

    if (candidate < 0)
    {
        return false;
    }

    // Count digits without floating point operations
    int temp = candidate;
    int exponent = 0;
    while (temp > 0)
    {
        exponent++;
        temp /= 10;
    }

    // Precompute powers for digits 0-9 to avoid repeated pow() calls
    int powers[10];
    int base = 1;
    for (int i = 0; i < 10; i++)
    {
        powers[i] = base;
        for (int j = 1; j < exponent; j++)
        {
            powers[i] *= i;
        }
    }

    int sum = 0;
    temp = candidate;

    do
    {
        int digit = temp % 10;
        sum += powers[digit];
        temp /= 10;

        if (sum > candidate)
        {
            return false;
        }

    } while (temp > 0);

    return (sum == candidate);
}