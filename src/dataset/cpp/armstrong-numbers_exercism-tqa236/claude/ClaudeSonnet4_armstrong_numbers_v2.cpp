#include "armstrong_numbers.h"

bool armstrong_numbers::is_armstrong_number(int number) {
  if (number < 0) return false;
  if (number < 10) return true;
  
  int length = 0;
  int temp = number;
  while (temp > 0) {
    length++;
    temp /= 10;
  }
  
  int number_copy = number;
  int armstrong_sum = 0;
  
  while (number_copy > 0) {
    int digit = number_copy % 10;
    number_copy /= 10;
    
    int digit_power = 1;
    for (int i = 0; i < length; i++) {
      digit_power *= digit;
    }
    
    armstrong_sum += digit_power;
  }
  
  return armstrong_sum == number;
}