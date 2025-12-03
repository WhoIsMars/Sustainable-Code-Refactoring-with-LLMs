#include "perfect_numbers.h"

kind classify_number(int number)
{
    if (number <= 0)
    {
        return ERROR;
    }

    if (number == 1)
    {
        return DEFICIENT_NUMBER;
    }

    int sum = 1;
    int sqrt_num = 1;
    
    while (sqrt_num * sqrt_num < number)
    {
        sqrt_num++;
    }

    for (int candidate = 2; candidate <= sqrt_num; candidate++)
    {
        if (number % candidate == 0)
        {
            sum += candidate;
            int complement = number / candidate;
            if (complement != candidate)
            {
                sum += complement;
            }
        }
    }

    if (sum == number)
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