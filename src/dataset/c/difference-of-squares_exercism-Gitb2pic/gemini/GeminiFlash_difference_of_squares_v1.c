#include "difference_of_squares.h"

unsigned int square_of_sum(unsigned int n) {
  unsigned int sum = n * (n + 1) / 2;
  return sum * sum;
}

unsigned int sum_of_squares(unsigned int n) {
  return n * (n + 1) * (2 * n + 1) / 6;
}

unsigned int difference_of_squares(unsigned int n) {
  unsigned int sum_of_nums = n * (n + 1) / 2;
  unsigned int square_of_sum_val = sum_of_nums * sum_of_nums;
  unsigned int sum_of_squares_val = n * (n + 1) * (2 * n + 1) / 6;
  return square_of_sum_val - sum_of_squares_val;
}