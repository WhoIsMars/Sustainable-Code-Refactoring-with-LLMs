#include "difference_of_squares.h"
#include <stdint.h>

unsigned int sum_of_squares(unsigned int number)
{
    uint32_t sum = 0;
    for (uint8_t i = 1; i <= number; i++)
    {
        sum += i * i;
    }

    return sum;
}

unsigned int square_of_sum(unsigned int number)
{
    uint32_t sum = 0;
    for (uint8_t i = 1; i <= number; i++)
    {
        sum += i;
    }

    return sum * sum;
}

unsigned int difference_of_squares(unsigned int number)
{
    return square_of_sum(number) - sum_of_squares(number);
}
