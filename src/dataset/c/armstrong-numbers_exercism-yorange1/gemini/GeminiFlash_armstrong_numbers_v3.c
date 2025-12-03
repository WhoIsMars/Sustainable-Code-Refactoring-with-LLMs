#include "armstrong_numbers.h"

#include <stdbool.h>
#include <stdint.h>

bool is_armstrong_number(int candidate) {
  if (candidate == 0) {
    return true;
  }

  int exponent = 0;
  int temp = candidate;
  while (temp > 0) {
    exponent++;
    temp /= 10;
  }

  int sum = 0;
  temp = candidate;
  while (temp > 0) {
    int digit = temp % 10;
    int power = 1;
    for (int i = 0; i < exponent; i++) {
      power *= digit;
    }
    if (power > (candidate - sum)) {
      return false;
    }
    sum += power;
    if (sum > candidate) {
      return false;
    }
    temp /= 10;
  }

  return (sum == candidate);
}