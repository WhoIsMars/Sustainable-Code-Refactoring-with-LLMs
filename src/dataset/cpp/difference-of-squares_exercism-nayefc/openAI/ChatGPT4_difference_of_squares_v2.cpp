#include "difference_of_squares.h"

int squares::square_of_sums(int n) {
    int sum = n * (n + 1) / 2; // Using the formula for the sum of the first n natural numbers
    return sum * sum;
}

int squares::sum_of_squares(int n) {
    return n * (n + 1) * (2 * n + 1) / 6; // Using the formula for the sum of squares of the first n natural numbers
}

int squares::difference(int n) {
    return squares::square_of_sums(n) - squares::sum_of_squares(n);
}