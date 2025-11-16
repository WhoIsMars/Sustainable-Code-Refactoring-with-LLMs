#include "armstrong_numbers.h"

bool armstrong_numbers::is_armstrong_number(int number) {
  if (number < 0) return false;
  if (number < 10) return true;
  
  // Count digits without string conversion
  int length = 0;
  int temp = number;
  while (temp > 0) {
    temp /= 10;
    ++length;
  }
  
  // Precompute powers for digits 0-9
  int powers[10];
  for (int i = 0; i < 10; ++i) {
    int power = 1;
    for (int j = 0; j < length; ++j) {
      power *= i;
    }
    powers[i] = power;
  }
  
  int number_copy = number;
  int armstrong_sum = 0;
  
  while (number_copy > 0) {
    int digit = number_copy % 10;
    number_copy /= 10;
    armstrong_sum += powers[digit];
  }
  
  return armstrong_sum == number;
}