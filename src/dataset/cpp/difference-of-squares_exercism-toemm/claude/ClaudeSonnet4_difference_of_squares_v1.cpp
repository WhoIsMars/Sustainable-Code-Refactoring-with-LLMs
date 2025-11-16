#include "difference_of_squares.h"

namespace difference_of_squares {

int square_of_sum(int i) {
    // Use arithmetic series formula: sum = n(n+1)/2
    int sum = i * (i + 1) / 2;
    return sum * sum;
}

int sum_of_squares(int i) {
    // Use formula for sum of squares: n(n+1)(2n+1)/6
    return i * (i + 1) * (2 * i + 1) / 6;
}

int difference(int i) {
    return square_of_sum(i) - sum_of_squares(i);
}

}  // namespace difference_of_squares