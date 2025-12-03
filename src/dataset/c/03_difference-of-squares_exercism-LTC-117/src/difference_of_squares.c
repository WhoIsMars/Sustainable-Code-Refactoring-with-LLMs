#include "difference_of_squares.h"


unsigned int sum_of_squares(unsigned int number)
{
    unsigned int result = 0;

    for (unsigned int i = 0; i <= number; i++) {
        result += (i * i);
    }

    return result;
}


unsigned int square_of_sum(unsigned int number)
{
    unsigned int result = 0;

    for (unsigned int i = 0; i <= number; i++) {
        result += i;
    }

    return (result * result);
}


unsigned int difference_of_squares(unsigned int number)
{
    unsigned int sum_squares = sum_of_squares(number);
    unsigned int square_sum = square_of_sum(number);

    return (square_sum - sum_squares);
}
