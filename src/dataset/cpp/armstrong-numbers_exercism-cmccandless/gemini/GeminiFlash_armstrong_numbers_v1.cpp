#include "armstrong_numbers.h"

namespace armstrong_numbers {

bool is_armstrong_number(int num) {
  if (num < 0) return false;

  int num_copy = num;
  int num_digits = 0;
  while (num_copy != 0) {
    num_copy /= 10;
    num_digits++;
  }

  num_copy = num;
  int sum = 0;
  while (num_copy != 0) {
    int digit = num_copy % 10;
    int power = 1;
    for (int i = 0; i < num_digits; ++i) {
      power *= digit;
    }
    if (sum > __INT_MAX__ - power) return false; // Check for potential overflow
    sum += power;
    num_copy /= 10;
  }

  return sum == num;
}

}  // namespace armstrong_numbers