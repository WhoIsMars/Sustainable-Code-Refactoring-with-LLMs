#include "difference_of_squares.h"

#include <numeric>

int squares::square_of_sums(int n) {
    long long sum = static_cast<long long>(n) * (n + 1) / 2;
    return static_cast<int>(sum * sum);
}

int squares::sum_of_squares(int n) {
    long long sum = static_cast<long long>(n) * (n + 1) * (2 * n + 1) / 6;
    return static_cast<int>(sum);
}

int squares::difference(int n) {
    return squares::square_of_sums(n) - squares::sum_of_squares(n);
}