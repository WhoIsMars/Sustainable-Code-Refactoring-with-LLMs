#include "difference_of_squares.h"

namespace squares {
    long square_of_sums(long N) {
        if (N < 2) return 0;
        long sum = N * (N + 1) / 2;
        return sum * sum;
    }

    long sum_of_squares(long N) {
        return N * (N + 1) * (2 * N + 1) / 6;
    }

    long difference(long N) {
        long squareSum = square_of_sums(N);
        long sumSquares = sum_of_squares(N);
        return squareSum - sumSquares;
    }
}