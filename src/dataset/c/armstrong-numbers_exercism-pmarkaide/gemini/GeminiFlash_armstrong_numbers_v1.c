#include "armstrong_numbers.h"
#include <stdbool.h>
#include <stdio.h>

bool is_armstrong_number(int candidate) {
  if (candidate < 0) {
    return false;
  }

  int num = candidate;
  int num_digits = 0;
  int temp = candidate;

  // Calculate the number of digits
  while (temp != 0) {
    temp /= 10;
    num_digits++;
  }

  int res = 0;
  temp = candidate;

  while (temp != 0) {
    int digit = temp % 10;
    int power = 1;
    for (int i = 0; i < num_digits; i++) {
      power *= digit;
    }
    if (res > __INT_MAX__ - power) return false;
    res += power;
    temp /= 10;
  }

  return res == candidate;
}