#include "difference_of_squares.h"

unsigned int square_of_sum(unsigned int n){
  unsigned int sum = (n * (n + 1)) >> 1;
  return sum * sum;
}

unsigned int sum_of_squares(unsigned int n){
  return (n * (n + 1) * ((n << 1) + 1)) / 6;
}

unsigned int difference_of_squares(unsigned int n)
{
  unsigned int sum = (n * (n + 1)) >> 1;
  return sum * sum - (n * (n + 1) * ((n << 1) + 1)) / 6;
}