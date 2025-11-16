#include "difference_of_squares.h"

namespace difference_of_squares {

    unsigned int square_of_sum(unsigned int n) {
        const unsigned int sum = (n * (n + 1)) >> 1;
        return sum * sum;
    }

    unsigned int sum_of_squares(unsigned int n) {
        return n * (n + 1) * (2 * n + 1) / 6;
    }

    unsigned int difference(unsigned int n) {
        const unsigned int sum = (n * (n + 1)) >> 1;
        const unsigned int sum_squared = sum * sum;
        const unsigned int squares_sum = n * (n + 1) * (2 * n + 1) / 6;
        return sum_squared - squares_sum;
    }

}  // namespace difference_of_squares