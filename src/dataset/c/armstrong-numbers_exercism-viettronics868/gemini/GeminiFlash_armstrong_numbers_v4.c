#include "armstrong_numbers.h"
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

bool is_armstrong_number(int candidate) {
  if (candidate < 0) {
    return false;
  }

  int num_digits = 0;
  int temp = candidate;
  while (temp != 0) {
    temp /= 10;
    num_digits++;
  }

  if (num_digits == 0) {
    return true; // Consider 0 an Armstrong number
  }

  int sum = 0;
  temp = candidate;
  while (temp != 0) {
    int digit = temp % 10;
    temp /= 10;

    double power = 1.0;
    for (int i = 0; i < num_digits; ++i) {
      power *= digit;
    }

    if (power > INT_MAX - sum) {
      return false; // Prevent integer overflow
    }
    sum += (int)power;
  }

  return sum == candidate;
}