#include "armstrong_numbers.h"

#include <math.h>

bool is_armstrong_number(uint32_t candidate) {
  if (candidate == 0) {
    return true;
  }

  uint32_t temp = candidate;
  int num_digits = 0;
  while (temp != 0) {
    temp /= 10;
    num_digits++;
  }

  uint32_t sum = 0;
  temp = candidate;
  while (temp != 0) {
    int digit = temp % 10;
    sum += pow(digit, num_digits);
    temp /= 10;
  }

  return sum == candidate;
}