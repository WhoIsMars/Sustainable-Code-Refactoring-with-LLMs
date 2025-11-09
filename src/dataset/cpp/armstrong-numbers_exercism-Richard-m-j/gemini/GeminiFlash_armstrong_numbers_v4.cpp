#include "armstrong_numbers.h"
#include <cmath>
#include <numeric>
#include <vector>

namespace armstrong_numbers {

bool is_armstrong_number(int input) {
  if (input < 0) return false;

  if (input == 0) return true;

  int num_digits = 0;
  int temp = input;
  while (temp > 0) {
    temp /= 10;
    num_digits++;
  }

  temp = input;
  long sum = 0;
  while (temp > 0) {
    int digit = temp % 10;
    long power = 1;
    for (int i = 0; i < num_digits; ++i) {
      power *= digit;
      if (power > input) return false;
    }
    sum += power;
    if (sum > input) return false;
    temp /= 10;
  }

  return sum == input;
}

} // namespace armstrong_numbers