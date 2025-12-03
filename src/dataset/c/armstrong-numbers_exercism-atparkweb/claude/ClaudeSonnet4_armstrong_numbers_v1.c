#include "armstrong_numbers.h"
#include <stdbool.h>

bool is_armstrong_number(int candidate) {
  if (candidate == 0)
    return true;

  int numDigits = 0;
  int temp = candidate;
  
  // Count digits
  while (temp > 0) {
    temp /= 10;
    numDigits++;
  }

  // All single digit numbers are Armstrong
  if (numDigits == 1)
    return true;

  int total = 0;
  temp = candidate;
  
  // Calculate sum without storing digits
  while (temp > 0) {
    int digit = temp % 10;
    
    // Manual power calculation to avoid floating point operations
    int power = 1;
    for (int i = 0; i < numDigits; i++) {
      power *= digit;
    }
    
    total += power;
    temp /= 10;
  }

  return candidate == total;
}