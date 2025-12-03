#include "difference_of_squares.h"

unsigned int sum_of_squares(unsigned int number) {
  return number * (number + 1) * (2 * number + 1) / 6;
}

unsigned int square_of_sum(unsigned int number) {
  unsigned int sum = number * (number + 1) / 2;
  return sum * sum;
}

unsigned int difference_of_squares(unsigned int number) {
  unsigned int sum_of_sq = sum_of_squares(number);
  unsigned int square_of_sm = square_of_sum(number);

  return square_of_sm - sum_of_sq;
}