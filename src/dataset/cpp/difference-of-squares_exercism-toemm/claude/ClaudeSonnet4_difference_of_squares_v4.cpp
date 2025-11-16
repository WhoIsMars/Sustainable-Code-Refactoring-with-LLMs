#include "difference_of_squares.h"

namespace difference_of_squares {

int square_of_sum(int i) {
    const long long sum = static_cast<long long>(i) * (i + 1) / 2;
    return static_cast<int>(sum * sum);
}

int sum_of_squares(int i) {
    const long long result = static_cast<long long>(i) * (i + 1) * (2 * i + 1) / 6;
    return static_cast<int>(result);
}

int difference(int i) {
    const long long sum = static_cast<long long>(i) * (i + 1) / 2;
    const long long square_of_sum_val = sum * sum;
    const long long sum_of_squares_val = static_cast<long long>(i) * (i + 1) * (2 * i + 1) / 6;
    return static_cast<int>(square_of_sum_val - sum_of_squares_val);
}

}  // namespace difference_of_squares