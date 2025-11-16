#include "difference_of_squares.h"

namespace difference_of_squares {

    unsigned int square_of_sum(unsigned int n) {
        unsigned int sum = n * (n + 1) / 2;
        return sum * sum;
    }

    unsigned int sum_of_squares(unsigned int n) {
        return n * (n + 1) * (2 * n + 1) / 6;
    }

    unsigned int difference(unsigned int n) {
        unsigned int sum = n * (n + 1) / 2;
        unsigned int squareSum = sum * sum;
        unsigned int sumSquares = n * (n + 1) * (2 * n + 1) / 6;
        return squareSum - sumSquares;
    }

}  // namespace difference_of_squares