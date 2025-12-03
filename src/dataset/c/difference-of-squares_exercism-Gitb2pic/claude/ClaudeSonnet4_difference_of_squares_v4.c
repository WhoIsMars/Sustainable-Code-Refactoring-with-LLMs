#include "difference_of_squares.h"

unsigned int square_of_sum(unsigned int n) {
    const unsigned int sum = (n * (n + 1)) >> 1;
    return sum * sum;
}

unsigned int sum_of_squares(unsigned int n) {
    return (n * (n + 1) * ((n << 1) + 1)) / 6;
}

unsigned int difference_of_squares(unsigned int n) {
    const unsigned int sum = (n * (n + 1)) >> 1;
    const unsigned int sum_sq = sum * sum;
    const unsigned int sq_sum = (n * (n + 1) * ((n << 1) + 1)) / 6;
    return sum_sq - sq_sum;
}