#include "perfect_numbers.h"

kind classify_number(int number)
{
    if (number <= 0)
    {
        return ERROR;
    }

    int sum = 1;
    int sqrt_number = (int)sqrt(number);

    for (int candidate = 2; candidate <= sqrt_number; candidate++)
    {
        if (number % candidate == 0)
        {
            int complement = number / candidate;
            sum += candidate;
            if (complement != candidate)
            {
                sum += complement;
            }
        }
    }

    if (sum == number && number != 1)
    {
        return PERFECT_NUMBER;
    }
    else if (sum > number)
    {
        return ABUNDANT_NUMBER;
    }
    else
    {
        return DEFICIENT_NUMBER;
    }
}