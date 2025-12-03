#include "perfect_numbers.h"
#include <math.h>

kind classify_number(int number) {
  if (number < 1) return ERROR;

  if (number == 1) return DEFICIENT_NUMBER;

  int sum = 1;
  int limit = (int)sqrt(number);

  for (int i = 2; i <= limit; i++) {
    if (number % i == 0) {
      sum += i;
      int quotient = number / i;
      if (quotient != i) {
        sum += quotient;
      }
    }
  }

  if (sum == number) return PERFECT_NUMBER;
  if (sum > number) return ABUNDANT_NUMBER;
  return DEFICIENT_NUMBER;
}