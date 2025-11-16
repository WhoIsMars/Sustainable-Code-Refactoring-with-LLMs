#include "difference_of_squares.h"

namespace difference_of_squares {

    unsigned int square_of_sum(unsigned int n) {
        return (n * (n + 1) / 2) * (n * (n + 1) / 2);
    }

    unsigned int sum_of_squares(unsigned int n) {
        return n * (n + 1) * (2 * n + 1) / 6;
    }

    unsigned int difference(unsigned int n) {
        unsigned int sum = n * (n + 1) / 2;
        return (sum * sum) - (n * (n + 1) * (2 * n + 1) / 6);
    }

}  // namespace difference_of_squares