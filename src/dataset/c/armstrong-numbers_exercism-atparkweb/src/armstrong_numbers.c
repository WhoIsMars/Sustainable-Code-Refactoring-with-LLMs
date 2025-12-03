#include "armstrong_numbers.h"
#include <math.h>
#include <stdbool.h>

bool is_armstrong_number(int candidate) {
  if (candidate == 0)
    return true;

  // Assuming no more than 10 digits (i.e. 32 bit integer max value)
  int digits[10];

  int numDigits = 0;
  int number = candidate;

  while (number > 0) {
    // Get the last digit
    digits[numDigits] = number % 10;

    // Remove the last digit
    number /= 10;

    numDigits++;
  }

  // All single digit numbers are Armstrong
  if (numDigits == 1)
    return true;

  int total = 0;
  for (int i = 0; i < numDigits; i++) {
    total += pow(digits[i], numDigits);
  }

  return candidate == total;
}
