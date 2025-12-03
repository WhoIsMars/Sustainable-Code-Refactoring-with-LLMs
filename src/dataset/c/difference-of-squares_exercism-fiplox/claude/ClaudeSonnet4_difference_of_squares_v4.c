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
    unsigned int n_plus_1 = number + 1;
    unsigned int sum = number * n_plus_1 / 2;
    unsigned int sum_squared = sum * sum;
    unsigned int sum_of_sq = number * n_plus_1 * (2 * number + 1) / 6;
    return sum_squared - sum_of_sq;
}