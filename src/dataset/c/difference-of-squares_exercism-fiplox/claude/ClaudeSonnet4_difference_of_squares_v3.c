#include "difference_of_squares.h"

unsigned int sum_of_squares(unsigned int number)
{
    return number * (number + 1) * (2 * number + 1) / 6;
}

unsigned int square_of_sum(unsigned int number)
{
    unsigned int sum = number * (number + 1) / 2;
    return sum * sum;
}

unsigned int difference_of_squares(unsigned int number)
{
    unsigned int n_squared = number * number;
    unsigned int n_cubed = n_squared * number;
    return (3 * n_squared * n_squared + 2 * n_cubed - 3 * n_squared - number) / 12;
}