#include "armstrong_numbers.h"

bool is_armstrong_number(int candidate)
{
    if (candidate < 0)
        return false;

    int num_digits = 0, temp = candidate;
    while (temp > 0)
    {
        temp /= 10;
        num_digits++;
    }

    int res = 0, num = candidate;
    while (num > 0)
    {
        int digit = num % 10;
        int power = 1;
        for (int i = 0; i < num_digits; i++)
        {
            power *= digit;
        }
        res += power;
        if (res > candidate)
            return false;
        num /= 10;
    }

    return res == candidate;
}