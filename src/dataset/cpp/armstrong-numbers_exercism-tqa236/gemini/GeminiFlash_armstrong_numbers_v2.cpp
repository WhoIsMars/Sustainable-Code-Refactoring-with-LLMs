#include "armstrong_numbers.h"

#include <cmath> // for std::pow
#include <algorithm> // for std::transform

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

    armstrong_sum += std::pow(digit, num_digits);
    if (armstrong_sum > number) return false; // Early exit optimization
  }

  return armstrong_sum == number;
}