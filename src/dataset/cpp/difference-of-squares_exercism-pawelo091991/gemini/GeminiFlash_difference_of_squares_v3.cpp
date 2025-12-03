#include "difference_of_squares.h"
#include <numeric>

int squares::square_of_sum(int number) {
    long long sum = static_cast<long long>(number) * (number + 1) / 2;
    return sum * sum;
}

int squares::sum_of_squares(int number) {
    return number * (number + 1) * (2 * number + 1) / 6;
}

int squares::difference(int number) {
    return square_of_sum(number) - sum_of_squares(number);
}