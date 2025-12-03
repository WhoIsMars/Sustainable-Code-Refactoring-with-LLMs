#include "difference_of_squares.h"

int difference_of_squares::square_of_sum(int num) {
  long long sum = static_cast<long long>(num) * (num + 1) / 2;
  return sum * sum;
}

int difference_of_squares::sum_of_squares(int num) {
  return num * (num + 1) * (2 * num + 1) / 6;
}

int difference_of_squares::difference(int num) {
  return square_of_sum(num) - sum_of_squares(num);
}