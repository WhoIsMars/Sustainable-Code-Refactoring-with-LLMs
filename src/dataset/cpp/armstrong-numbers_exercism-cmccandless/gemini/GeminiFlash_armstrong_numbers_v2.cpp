#include <cmath>

#include "armstrong_numbers.h"

namespace armstrong_numbers {

bool is_armstrong_number(int number) {
  if (number < 0) {
    return false;
  }

  if (number == 0) {
    return true;
  }

  int num = number;
  int num_digits = 0;
  while (num != 0) {
    num /= 10;
    num_digits++;
  }

  int sum = 0;
  num = number;
  while (num != 0) {
    int digit = num % 10;
    int power = 1;
    for (int i = 0; i < num_digits; ++i) {
      power *= digit;
    }
    if (sum > INT_MAX - power) {
        return false;
    }
    sum += power;
    num /= 10;
  }

  return sum == number;
}

} // namespace armstrong_numbers