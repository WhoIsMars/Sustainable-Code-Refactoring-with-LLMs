#include "difference_of_squares.h"

namespace difference_of_squares {

    int square_of_sum(int n) {
        long long sum = static_cast<long long>(n) * (n + 1) / 2;
        return static_cast<int>(sum * sum);
    }

    int sum_of_squares(int n) {
        long long n_ll = static_cast<long long>(n);
        return static_cast<int>((n_ll * (n_ll + 1) * (2 * n_ll + 1)) / 6);
    }

    int difference(int n) {
        return square_of_sum(n) - sum_of_squares(n);
    }
} // namespace difference_of_squares