#include "difference_of_squares.h"


unsigned int square_of_sum(unsigned int number)
{
    int sum = 1;
    for (unsigned i = 2; i <= number; ++i)
    {
        sum += i;
    }
    return sum * sum;
}
unsigned int sum_of_squares(unsigned int number)
{
    int sum = 0;
    for (unsigned i = 0; i <= number; ++i)
    {
        sum += (i*i);
    }
    return sum;
}

unsigned int difference_of_squares(unsigned int number)
{
    return square_of_sum(number) - sum_of_squares(number);
}
