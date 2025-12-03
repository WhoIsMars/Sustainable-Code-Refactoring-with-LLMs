#include "armstrong_numbers.h"

#include <stdio.h>
#include <stdint.h>

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

    int exponent = 0, temp = candidate;
    while (temp > 0)
    {
        temp /= 10;
        exponent++;
    }

    int sum = 0;
    temp = candidate;
    while (temp > 0)
    {
        int digit = temp % 10;
        int power = 1;
        for (int i = 0; i < exponent; i++)
        {
            power *= digit;
        }
        sum += power;
        if (sum > candidate)
        {
            return false;
        }
        temp /= 10;
    }

    return (sum == candidate);
}