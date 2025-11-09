#include "difference_of_squares.h"

namespace difference_of_squares
{
    int square_of_sum(int n)
    {
        // Use arithmetic series formula: sum = n(n+1)/2
        int sum = n * (n + 1) / 2;
        return sum * sum;
    }
    
    int sum_of_squares(int n)
    {
        // Use formula for sum of squares: n(n+1)(2n+1)/6
        return n * (n + 1) * (2 * n + 1) / 6;
    }
    
    int difference(int n)
    {
        return square_of_sum(n) - sum_of_squares(n);
    }
} // namespace difference_of_squares