#include "armstrong_numbers.h"
#include <stdbool.h>
#include <stdint.h>

bool is_armstrong_number(int candidate) {
  if (candidate < 0) {
    return false;
  }

  int num = candidate;
  int num_digits = 0;

  if (num == 0) {
    num_digits = 1;
  } else {
    while (num > 0) {
      num_digits++;
      num /= 10;
    }
  }

  num = candidate;
  int64_t res = 0;

  while (num > 0) {
    int digit = num % 10;
    int64_t power = 1;
    for (int i = 0; i < num_digits; ++i) {
      power *= digit;
      if (power > candidate) break;
    }
    if (power > candidate) return false;
    res += power;
    if (res > candidate) return false;
    num /= 10;
  }

  return (res == candidate);
}