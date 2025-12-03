#include "armstrong_numbers.h"
#include <stdbool.h>

bool is_armstrong_number(int candidate) {
  if (candidate < 10)
    return true;

  int number = candidate;
  int numDigits = 0;
  int total = 0;

  // Calculate the number of digits
  for (int temp = number; temp > 0; temp /= 10) {
    numDigits++;
  }

  // Calculate the Armstrong total
  for (int temp = number; temp > 0; temp /= 10) {
    int digit = temp % 10;
    int power = 1;
    for (int i = 0; i < numDigits; i++) {
      power *= digit;
    }
    total += power;
    if (total > candidate) {
      return false; // Early exit if total exceeds candidate
    }
  }

  return candidate == total;
}