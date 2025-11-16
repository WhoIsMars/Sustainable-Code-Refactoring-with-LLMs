#include "difference_of_squares.h"

namespace difference_of_squares {
    int square_of_sum(int limit) {
        int sum = (limit * (limit + 1)) / 2;
        return sum * sum;
    }

    int sum_of_squares(int limit) {
        return (limit * (limit + 1) * (2 * limit + 1)) / 6;
    }

    int difference(int limit) {
        int sum = (limit * (limit + 1)) / 2;
        int square_of_sum_result = sum * sum;
        int sum_of_squares_result = (limit * (limit + 1) * (2 * limit + 1)) / 6;
        return square_of_sum_result - sum_of_squares_result;
    }

}  // namespace difference_of_squares