#include "difference_of_squares.h"

namespace difference_of_squares {

int square_of_sum(int limit) {
    const int sum = limit * (limit + 1) / 2;
    return sum * sum;
}

int sum_of_squares(int limit) {
    return limit * (limit + 1) * (2 * limit + 1) / 6;
}

int difference(int limit) {
    const int sum = limit * (limit + 1) / 2;
    const int sum_squared = sum * sum;
    const int squares_sum = limit * (limit + 1) * (2 * limit + 1) / 6;
    return sum_squared - squares_sum;
}

}  // namespace difference_of_squares