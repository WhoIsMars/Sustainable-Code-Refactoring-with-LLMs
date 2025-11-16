#include "difference_of_squares.h"
#include <iostream>

namespace squares {
    long square_of_sums(long N) {
        if (N < 2)
            return 0;

        long sum = N * (N + 1) / 2; // Use formula for sum of first N natural numbers
        return sum * sum;
    }

    long sum_of_squares(long N) {
        // Use formula for sum of squares of first N natural numbers
        return (N * (N + 1) * (2 * N + 1)) / 6;
    }

    long difference(long N) {
        return square_of_sums(N) - sum_of_squares(N);
    }
}