#include "difference_of_squares.h"

namespace difference_of_squares {

    int square_of_sum(int n) {
        const int sum = (n * (n + 1)) >> 1;
        return sum * sum;
    }

    int sum_of_squares(int n) {
        return (n * (n + 1) * (2 * n + 1)) / 6;
    }

    int difference(int n) {
        const int sum = (n * (n + 1)) >> 1;
        const int square_of_sum_val = sum * sum;
        const int sum_of_squares_val = (n * (n + 1) * (2 * n + 1)) / 6;
        return square_of_sum_val - sum_of_squares_val;
    }

} // namespace difference_of_squares