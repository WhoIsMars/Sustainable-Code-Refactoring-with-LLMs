#include "difference_of_squares.h"

namespace difference_of_squares {

int square_of_sum(int limit) {
    // Use arithmetic series formula: sum = n(n+1)/2
    int sum = limit * (limit + 1) / 2;
    return sum * sum;
}

int sum_of_squares(int limit) {
    // Use formula for sum of squares: n(n+1)(2n+1)/6
    return limit * (limit + 1) * (2 * limit + 1) / 6;
}

int difference(int limit) {
    return square_of_sum(limit) - sum_of_squares(limit);
}

}  // namespace difference_of_squares