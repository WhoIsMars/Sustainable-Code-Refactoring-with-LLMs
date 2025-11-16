#include "armstrong_numbers.h"

#include <cmath>

using std::pow;

bool armstrong_numbers::is_armstrong_number(int number) {
  if (number < 0) return false;
  if (number < 10) return true;
  
  int temp = number;
  int length = 0;
  while (temp > 0) {
    temp /= 10;
    ++length;
  }
  
  int number_copy = number;
  int armstrong_sum = 0;
  
  while (number_copy > 0) {
    int digit = number_copy % 10;
    number_copy /= 10;
    armstrong_sum += static_cast<int>(pow(digit, length));
  }
  
  return armstrong_sum == number;
}