#include "difference_of_squares.h"

int squares::square_of_sums(int n) {
    int sum = n * (n + 1) / 2;
    return sum * sum;
}

int squares::sum_of_squares(int n) {
    return n * (n + 1) * (2 * n + 1) / 6;
}

int squares::difference(int n) {
    int sum = n * (n + 1) / 2;
    int square_of_sums = sum * sum;
    int sum_of_squares = n * (n + 1) * (2 * n + 1) / 6;
    return square_of_sums - sum_of_squares;
}