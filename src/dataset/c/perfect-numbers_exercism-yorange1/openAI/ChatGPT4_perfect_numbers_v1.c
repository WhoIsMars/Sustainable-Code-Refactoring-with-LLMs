#include "perfect_numbers.h"

kind classify_number(int number)
{
    if (number <= 0)
    {
        return ERROR;
    }

    int sum = 1; // 1 is always a divisor
    int sqrt_number = (int)sqrt(number);

    for (int candidate = 2; candidate <= sqrt_number; candidate++)
    {
        if (number % candidate == 0)
        {
            int pair = number / candidate;
            sum += candidate;
            if (pair != candidate) // Avoid adding the square root twice
            {
                sum += pair;
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