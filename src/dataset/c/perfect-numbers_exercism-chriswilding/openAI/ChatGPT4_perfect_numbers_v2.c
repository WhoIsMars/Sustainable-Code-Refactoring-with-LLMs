#include "perfect_numbers.h"

kind classify_number(int number) {
  if (number < 1) return ERROR;

  int sum = 1; // 1 is a divisor of all positive integers
  int sqrt_number = (int)sqrt(number);

  for (int i = 2; i <= sqrt_number; i++) {
    if (number % i == 0) {
      sum += i;
      int pair = number / i;
      if (i != pair) {
        sum += pair;
      }
    }
  }

  if (sum == number && number != 1) return PERFECT_NUMBER;
  if (sum > number) return ABUNDANT_NUMBER;
  return DEFICIENT_NUMBER;
}