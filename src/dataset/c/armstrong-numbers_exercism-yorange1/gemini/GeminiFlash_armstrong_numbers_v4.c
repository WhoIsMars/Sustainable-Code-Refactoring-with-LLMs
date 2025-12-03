#include "armstrong_numbers.h"

#include <stdbool.h>
#include <stdint.h>

bool is_armstrong_number(int candidate) {
  if (candidate < 0) {
    return false;
  }

  if (candidate == 0) {
    return true;
  }

  int num_digits = 0;
  int temp = candidate;
  while (temp > 0) {
    num_digits++;
    temp /= 10;
  }

  int sum = 0;
  temp = candidate;
  while (temp > 0) {
    int digit = temp % 10;
    int power = 1;
    for (int i = 0; i < num_digits; i++) {
      if (power > candidate / digit) {
        sum = candidate + 1;
        break;
      }
      power *= digit;
    }
    if (sum > candidate) break;
    sum += power;
    if (sum > candidate) break;
    temp /= 10;
  }

  return sum == candidate;
}