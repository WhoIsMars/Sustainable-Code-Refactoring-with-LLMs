#include "armstrong_numbers.h"

#include <cmath>

bool armstrong_numbers::is_armstrong_number(int number) {
  int length = 0, number_copy = number, armstrong_sum = 0, power_cache[10] = {0};

  while (number_copy > 0) {
    ++length;
    number_copy /= 10;
  }

  number_copy = number;
  for (int i = 0; i < 10; ++i) {
    power_cache[i] = std::pow(i, length);
  }

  while (number_copy > 0) {
    int digit = number_copy % 10;
    number_copy /= 10;
    armstrong_sum += power_cache[digit];
  }

  return armstrong_sum == number;
}