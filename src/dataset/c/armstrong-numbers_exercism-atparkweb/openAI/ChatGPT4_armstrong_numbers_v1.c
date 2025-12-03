#include "armstrong_numbers.h"
#include <stdbool.h>

bool is_armstrong_number(int candidate) {
  if (candidate < 10)
    return true;

  int number = candidate, numDigits = 0, total = 0, powerCache[10];

  // Calculate the number of digits and initialize power cache
  while (number > 0) {
    numDigits++;
    number /= 10;
  }

  number = candidate;

  // Precompute powers for digits 0-9
  for (int i = 0; i < 10; i++) {
    int power = 1;
    for (int j = 0; j < numDigits; j++) {
      power *= i;
    }
    powerCache[i] = power;
  }

  // Calculate the Armstrong total
  while (number > 0) {
    total += powerCache[number % 10];
    number /= 10;
  }

  return candidate == total;
}