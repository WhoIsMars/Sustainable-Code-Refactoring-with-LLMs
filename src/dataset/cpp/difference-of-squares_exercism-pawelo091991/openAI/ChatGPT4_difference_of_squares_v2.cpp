#include "difference_of_squares.h"
#include <cmath>

int squares::square_of_sum(int number) {
    int sum = number * (number + 1) / 2; // Use arithmetic series formula
    return sum * sum;
}

int squares::sum_of_squares(int number) {
    return (number * (number + 1) * (2 * number + 1)) / 6; // Use sum of squares formula
}

int squares::difference(int number) {
    return square_of_sum(number) - sum_of_squares(number);
}