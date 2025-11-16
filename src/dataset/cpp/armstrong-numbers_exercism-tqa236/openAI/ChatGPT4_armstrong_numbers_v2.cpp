#include "armstrong_numbers.h"

bool armstrong_numbers::is_armstrong_number(int number) {
  int length = 0, number_copy = number, armstrong_sum = 0;

  // Calculate the length of the number without converting to string
  for (int temp = number; temp > 0; temp /= 10) {
    ++length;
  }

  // Calculate Armstrong sum
  while (number_copy > 0) {
    int digit = number_copy % 10;
    number_copy /= 10;

    // Replace pow with manual multiplication for efficiency
    int digit_power = 1;
    for (int i = 0; i < length; ++i) {
      digit_power *= digit;
    }

    armstrong_sum += digit_power;
  }

  return armstrong_sum == number;
}