#include "difference_of_squares.h"

#include <cmath>

int squares::square_of_sum(int number) {
  // Use the formula for the sum of the first n natural numbers: n(n+1)/2
  long long sum = static_cast<long long>(number) * (number + 1) / 2;
  return static_cast<int>(sum * sum);
}

int squares::sum_of_squares(int number) {
  // Use the formula for the sum of the squares of the first n natural numbers: n(n+1)(2n+1)/6
  long long sum = static_cast<long long>(number) * (number + 1) * (2 * number + 1) / 6;
  return static_cast<int>(sum);
}

int squares::difference(int number) {
  return square_of_sum(number) - sum_of_squares(number);
}