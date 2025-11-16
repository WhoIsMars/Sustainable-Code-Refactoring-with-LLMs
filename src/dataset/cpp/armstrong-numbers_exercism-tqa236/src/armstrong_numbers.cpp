#include "armstrong_numbers.h"

#include <cmath>
#include <string>

using std::pow;
using std::to_string;

bool armstrong_numbers::is_armstrong_number(int number) {
  int length = to_string(number).length();
  int number_copy = number;
  int armstrong_sum = 0;

  while (number_copy > 0) {
    int digit = number_copy % 10;
    number_copy = number_copy / 10;
    armstrong_sum = armstrong_sum + pow(digit, length);
  }

  return armstrong_sum == number;
}
