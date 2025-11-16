#include "difference_of_squares.h"

#include <numeric>

int squares::square_of_sums(int n) {
    long long sum = static_cast<long long>(n) * (n + 1) / 2;
    return sum * sum;
}

int squares::sum_of_squares(int n) {
    return n * (n + 1) * (2 * n + 1) / 6;
}

int squares::difference(int n) {
    return square_of_sums(n) - sum_of_squares(n);
}