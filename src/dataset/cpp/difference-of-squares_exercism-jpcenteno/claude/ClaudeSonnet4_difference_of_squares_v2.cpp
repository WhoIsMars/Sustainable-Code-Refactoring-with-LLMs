#include "difference_of_squares.h"

namespace difference_of_squares {

    unsigned int square_of_sum(unsigned int n) {
        const auto sum = (n * (n + 1)) >> 1;
        return sum * sum;
    }

    unsigned int sum_of_squares(unsigned int n) {
        return n * (n + 1) * (2 * n + 1) / 6;
    }

    unsigned int difference(unsigned int n) {
        const auto sum = (n * (n + 1)) >> 1;
        const auto sum_sq = n * (n + 1) * (2 * n + 1) / 6;
        return sum * sum - sum_sq;
    }

}  // namespace difference_of_squares