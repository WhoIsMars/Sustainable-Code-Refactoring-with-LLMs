#include "difference_of_squares.h"


unsigned int square_of_sum(unsigned int n){

  unsigned int result = ((n * (n + 1)) / 2);
  return result * result;
}

unsigned int sum_of_squares(unsigned int n){
  unsigned int result = (n*(n + 1) * (2 * n  + 1) )/6;
  return result;
}
unsigned int difference_of_squares(unsigned int n)
{
  unsigned int a, b, diff;
  a = square_of_sum(n);
  b = sum_of_squares(n);
  return a - b;
}
