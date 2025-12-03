#include "armstrong_numbers.h"

bool is_armstrong_number(int candidate)
{
    if (candidate < 0)
        return false;

    int num_digits = 0, temp = candidate, res = 0;

    // Calculate the number of digits
    while (temp > 0)
    {
        temp /= 10;
        num_digits++;
    }

    temp = candidate;

    // Calculate the Armstrong sum
    while (temp > 0)
    {
        int digit = temp % 10;
        int power = 1;
        for (int i = 0; i < num_digits; i++)
        {
            power *= digit;
        }
        res += power;
        temp /= 10;
    }

    return res == candidate;
}