#include "difference_of_squares.h"

namespace difference_of_squares {

    int square_of_sum(int n) {
        long long sum = static_cast<long long>(n) * (n + 1) / 2;
        return static_cast<int>(sum * sum);
    }

    int sum_of_squares(int n) {
        return n * (n + 1) * (2 * n + 1) / 6;
    }

    int difference(int n) {
        long long sum = static_cast<long long>(n) * (n + 1) / 2;
        long long square_of_sum_val = sum * sum;
        long long sum_of_squares_val = static_cast<long long>(n) * (n + 1) * (2 * n + 1) / 6;
        return static_cast<int>(square_of_sum_val - sum_of_squares_val);
    }

} // namespace difference_of_squares