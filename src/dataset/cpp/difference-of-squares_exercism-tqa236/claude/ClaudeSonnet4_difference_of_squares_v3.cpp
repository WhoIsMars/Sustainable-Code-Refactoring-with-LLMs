#include "difference_of_squares.h"

int difference_of_squares::square_of_sum(int num) {
  int sum = (num * (num + 1)) >> 1;
  return sum * sum;
}

int difference_of_squares::sum_of_squares(int num) {
  return num * (num + 1) * (2 * num + 1) / 6;
}

int difference_of_squares::difference(int num) {
  int sum = (num * (num + 1)) >> 1;
  int square_of_sum = sum * sum;
  int sum_of_squares = num * (num + 1) * (2 * num + 1) / 6;
  return square_of_sum - sum_of_squares;
}