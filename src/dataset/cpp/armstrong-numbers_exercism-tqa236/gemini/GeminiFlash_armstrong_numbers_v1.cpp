#include "armstrong_numbers.h"

#include <cmath> // Required for std::pow
#include <algorithm> // Required for std::transform

bool armstrong_numbers::is_armstrong_number(int number) {
  if (number < 0) {
    return false;
  }

  std::string number_str = std::to_string(number);
  int length = number_str.length();
  int armstrong_sum = 0;

  for (char c : number_str) {
    int digit = c - '0';
    armstrong_sum += std::pow(digit, length);
  }

  return armstrong_sum == number;
}