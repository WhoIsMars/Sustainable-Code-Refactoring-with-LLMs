#include "difference_of_squares.h"
#include <stdint.h>

unsigned int sum_of_squares(unsigned int number)
{
    // Formula: n(n+1)(2n+1)/6
    uint64_t n = number;
    return (n * (n + 1) * (2 * n + 1)) / 6;
}

unsigned int square_of_sum(unsigned int number)
{
    // Formula: (n(n+1)/2)^2
    uint64_t n = number;
    uint64_t sum = (n * (n + 1)) / 2;
    return sum * sum;
}

unsigned int difference_of_squares(unsigned int number)
{
    return square_of_sum(number) - sum_of_squares(number);
}