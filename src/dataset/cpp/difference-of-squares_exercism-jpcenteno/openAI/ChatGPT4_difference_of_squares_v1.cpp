#include "difference_of_squares.h"

namespace difference_of_squares {

    unsigned int square_of_sum(unsigned int n) {
        unsigned int sum = (n * (n + 1)) / 2;
        return sum * sum;
    }

    unsigned int sum_of_squares(unsigned int n) {
        return n * (n + 1) * (2 * n + 1) / 6;
    }

    unsigned int difference(unsigned int n) {
        unsigned int sum = (n * (n + 1)) / 2;
        unsigned int square_sum = sum * sum;
        unsigned int sum_squares = n * (n + 1) * (2 * n + 1) / 6;
        return square_sum - sum_squares;
    }

}  // namespace difference_of_squares