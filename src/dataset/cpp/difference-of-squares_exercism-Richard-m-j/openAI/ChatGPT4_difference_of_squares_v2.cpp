#include "difference_of_squares.h"

namespace difference_of_squares
{
    int square_of_sum(int n)
    {
        int sum = n * (n + 1) / 2; // Using the formula for the sum of the first n natural numbers
        return sum * sum;
    }
    int sum_of_squares(int n)
    {
        return n * (n + 1) * (2 * n + 1) / 6; // Using the formula for the sum of the squares of the first n natural numbers
    }
    int difference(int n)
    {
        return square_of_sum(n) - sum_of_squares(n);
    }
} // namespace difference_of_squares