#include "armstrong_numbers.h"
#include <stdbool.h>

bool is_armstrong_number(int candidate) {
  if (candidate == 0) {
    return true;
  }

  int numDigits = 0;
  int temp = candidate;
  while (temp > 0) {
    temp /= 10;
    numDigits++;
  }

  if (numDigits == 1) {
    return true;
  }

  int total = 0;
  temp = candidate;
  while (temp > 0) {
    int digit = temp % 10;
    int power = 1;
    for (int i = 0; i < numDigits; i++) {
      power *= digit;
    }
    if (total > __INT_MAX__ - power) {
        return false;
    }
    total += power;
    temp /= 10;
  }

  return candidate == total;
}