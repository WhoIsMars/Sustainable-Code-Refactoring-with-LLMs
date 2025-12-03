#include "perfect_numbers.h"

int aliquot_sum(int number);

int classify_number(int number) 
{
    if (number <= 0) 
        return ERROR;

    int sum = aliquot_sum(number);

    if (sum == number) 
        return PERFECT_NUMBER;
     else if (sum > number) 
        return ABUNDANT_NUMBER;
     else 
        return DEFICIENT_NUMBER;
}

int aliquot_sum(int number) 
{
    int sum = 0;

    if (number <= 0) 
        return -1; 
    

    for (int i = 1; i <= number / 2; i++) 
    {
        if (number % i == 0) 
            sum += i;
    }

    return sum;
}