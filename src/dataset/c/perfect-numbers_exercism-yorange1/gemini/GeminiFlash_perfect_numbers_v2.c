#include "perfect_numbers.h"
#include <cmath>

kind classify_number(int number) {
  if (number <= 0) {
    return ERROR;
  }

  int sum = 1; // Start with 1 as it's always a divisor
  int sqrt_number = static_cast<int>(std::sqrt(number));

  if (sqrt_number * sqrt_number == number) {
        sum -= sqrt_number;
  }

  for (int i = 2; i <= sqrt_number; ++i) {
    if (number % i == 0) {
      sum += i;
      sum += number / i;
    }
  }

  if (sum == number) {
    return PERFECT_NUMBER;
  } else if (sum > number) {
    return ABUNDANT_NUMBER;
  } else {
    return DEFICIENT_NUMBER;
  }
}