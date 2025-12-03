#include "armstrong_numbers.h"
#include <stdbool.h>

bool is_armstrong_number(int candidate) {
  if (candidate < 0) {
    return false;
  }

  if (candidate == 0) {
    return true;
  }

  int numDigits = 0;
  int temp = candidate;
  while (temp > 0) {
    temp /= 10;
    numDigits++;
  }

  int total = 0;
  int number = candidate;
  while (number > 0) {
    int digit = number % 10;
    number /= 10;

    int power = 1;
    for (int i = 0; i < numDigits; ++i) {
      power *= digit;
    }

    if (total > __INT_MAX__ - power) {
      return false;
    }

    total += power;
  }

  return candidate == total;
}