#include "difference_of_squares.h"

namespace difference_of_squares {

int square_of_sum(int limit) {
    int sum = limit * (limit + 1) / 2;
    return sum * sum;
}

int sum_of_squares(int limit) {
    return limit * (limit + 1) * (2 * limit + 1) / 6;
}

int difference(int limit) {
    int sum = limit * (limit + 1) / 2;
    int sum_sq = limit * (limit + 1) * (2 * limit + 1) / 6;
    return sum * sum - sum_sq;
}

}  // namespace difference_of_squares