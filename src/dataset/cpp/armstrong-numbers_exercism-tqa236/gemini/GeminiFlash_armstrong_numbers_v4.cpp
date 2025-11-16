#include "armstrong_numbers.h"

#include <cmath>

bool armstrong_numbers::is_armstrong_number(int number) {
  if (number < 0) return false;

  int num_digits = 0;
  int temp = number;
  while (temp != 0) {
    temp /= 10;
    ++num_digits;
  }

  int armstrong_sum = 0;
  temp = number;
  while (temp != 0) {
    int digit = temp % 10;
    temp /= 10;

    int power = 1;
    for (int i = 0; i < num_digits; ++i) {
      power *= digit;
    }

    if (armstrong_sum > INT_MAX - power) return false;

    armstrong_sum += power;
  }

  return armstrong_sum == number;
}