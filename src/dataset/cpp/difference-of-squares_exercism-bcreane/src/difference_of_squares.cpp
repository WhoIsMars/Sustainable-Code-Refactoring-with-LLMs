#include "difference_of_squares.h"

int
squares::square_of_sums(int n)
{
    int square_of_sums = 0;
    for (int i = 1; i <= n; ++i) {
        square_of_sums += i;
    }

    return square_of_sums * square_of_sums;
}

int
squares::sum_of_squares(int n)
{
    int sum_of_squares = 0;
    for (int i = 1; i <= n; ++i) {
        sum_of_squares += i*i;
    }
    
    return sum_of_squares;
}

int
squares::difference(int n)
{
    return square_of_sums(n) - sum_of_squares(n);
}