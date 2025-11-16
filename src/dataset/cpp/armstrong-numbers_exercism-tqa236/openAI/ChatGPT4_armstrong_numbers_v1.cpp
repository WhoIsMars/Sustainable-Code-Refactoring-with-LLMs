#include "armstrong_numbers.h"

bool armstrong_numbers::is_armstrong_number(int number) {
  int length = 0, number_copy = number, armstrong_sum = 0;

  // Calculate the number of digits
  for (int temp = number; temp > 0; temp /= 10) {
    ++length;
  }

  // Calculate Armstrong sum
  while (number_copy > 0) {
    int digit = number_copy % 10;
    number_copy /= 10;

    int power = 1;
    for (int i = 0; i < length; ++i) {
      power *= digit;
    }

    armstrong_sum += power;
    if (armstrong_sum > number) { // Early exit if sum exceeds the number
      return false;
    }
  }

  return armstrong_sum == number;
}